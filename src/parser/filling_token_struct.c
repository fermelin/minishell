/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_token_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:02:13 by gevelynn          #+#    #+#             */
/*   Updated: 2021/01/11 14:48:19 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		is_special_symbol(t_all *all, char *str)
{
	if (str == NULL && all->is_semicolon)
		return (1);
	else if (what_redirection(str) != 0 || ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}

static	int		check_semicolon(t_all *all)
{
	if (all->is_semicolon == 1)
	{
		all->is_semicolon = 0;
		return (1);
	}
	return (0);
}

static	int		check_syntax_error_in_args(t_all *all, char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (is_special_symbol(all, array[i]) != 0 && array[i + 1] &&
			is_special_symbol(all, array[i + 1]) != 0)
			print_error_with_arg(SYNTAX_ERROR, array[i + 1], NULL);
		else if (what_redirection(array[i]) != 0 && array[i + 1] == NULL)
		{
			if (check_semicolon(all) == 1)
				print_error_with_arg(SYNTAX_ERROR, ";", NULL);
			else
				print_error_with_arg(SYNTAX_ERROR, "newline", NULL);
		}
		else
			continue ;
		break ;
	}
	if (array[i] != NULL)
	{
		all->exit_status = 2;
		return (-1);
	}
	return (0);
}

int				filling_struct(t_all *all, t_list *new, int len)
{
	char	**array;
	int		i;

	i = 0;
	if (!(array = ft_calloc(len + 1, sizeof(char *))))
		return (-1);
	while (new)
	{
		array[i] = new->content;
		new = new->next;
		i++;
	}
	if (check_syntax_error_in_args(all, array) != -1)
	{
		split_args_and_redirects(array, all, len);
		free(array);
	}
	else
	{
		free(array);
		return (-1);
	}
	return (0);
}
