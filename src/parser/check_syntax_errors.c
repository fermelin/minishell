/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:01:01 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/12 11:06:04 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	error_quotes(t_all *all, char *line)
{
	int i;
	int	one_quote;
	int	two_quote;

	i = 0;
	one_quote = 0;
	two_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			counting_quotes(line, &one_quote, &two_quote, i);
		i++;
	}
	if (one_quote % 2 != 0 || two_quote % 2 != 0)
	{
		if (one_quote % 2 != 0)
			print_error_with_arg(ERR_QUOTE, "\'", NULL);
		else
			print_error_with_arg(ERR_QUOTE, "\"", NULL);
		all->exit_status = 2;
		return (-1);
	}
	return (0);
}

static	int	second_check_syntax_error(char *line, t_all *all, int i)
{
	if (line && i >= 0)
	{
		while (line[i])
		{
			if ((line[i] == '|' || line[i] == '<' ||
				line[i] == '>' || line[i] == ';') && line[i + 1])
			{
				i++;
				while (ft_isspace(line[i]))
					i++;
				if (line[i] == '|' || line[i] == ';')
				{
					if (line[i] == ';')
						print_error_with_arg(SYNTAX_ERROR, ";", NULL);
					else if (line[i] == '|')
						print_error_with_arg(SYNTAX_ERROR, "|", NULL);
					all->exit_status = 2;
					return (-1);
				}
			}
			if (line[i])
				i++;
		}
	}
	return (0);
}

int			first_check_syntax_error(char *line, t_all *all)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == ';' || line[i] == '|')
	{
		if (line[i] == ';')
			print_error_with_arg(SYNTAX_ERROR, ";", NULL);
		else
			print_error_with_arg(SYNTAX_ERROR, "|", NULL);
		all->exit_status = 2;
		return (-1);
	}
	if (error_quotes(all, line) == -1)
		return (-1);
	if (second_check_syntax_error(line, all, i) == -1)
		return (-1);
	return (0);
}
