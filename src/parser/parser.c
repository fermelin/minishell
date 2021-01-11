/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:08:05 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/11 20:45:37 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		counting_quotes(char *str, int *one_quotes, int *two_quotes, int i)
{
	if (str[i] == '\'')
	{
		(*one_quotes)++;
		if ((*two_quotes) % 2 || (str[i - 1] == '\\' && (*one_quotes) % 2))
			(*one_quotes)++;
	}
	else if (str[i] == '\"')
	{
		(*two_quotes)++;
		if ((*one_quotes) % 2 || (str[i - 1] == '\\'))
			(*two_quotes)++;
	}
}

void		parser(char *str, t_all *all)
{
	int			i;
	int			start;
	int			one_quotes;
	int			two_quotes;

	i = -1;
	start = 0;
	one_quotes = 0;
	two_quotes = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			counting_quotes(str, &one_quotes, &two_quotes, i);
		else if ((str[i] == ';' && (i != 0 && str[i - 1] != '\\')) &&
				(one_quotes % 2 == 0 && two_quotes % 2 == 0))
		{
			if (line_search(str, all, start, i - 1) == -1)
				return ;
			execution(all);
			start = i + 1;
		}
	}
	line_search(str, all, start, i - 1);
}

int			is_terminating_pipe_in_line(char *line)
{
	int i;

	i = 0;
	if (line)
	{
		i = ft_strlen(line) - 1;
		while (i >= 0 && (line[i] == ' ' || line[i] == '\t'))
			i--;
		if (i > 0 && line[i] == '|')
		{
			ft_putstr_fd("pipe> ", 2);
			return (1);
		}
	}
	return (0);
}

char		*get_line(void)
{
	char	*line2;
	char	*line;
	int		ret;

	line2 = NULL;
	while ((ret = get_next_line(0, &line)) != 1 ||
		is_terminating_pipe_in_line(line) == 1)
	{
		if (ret == -1)
		{
			print_error("GNL", "", "error");
			return (NULL);
		}
		if ((!line || !(*line)) && (!line2 || !(*line2)))
		{
			free(line);
			return (NULL);
		}
		line2 = ft_strjoin_free(line2, line);
		free(line);
	}
	line2 = ft_strjoin_free(line2, line);
	free(line);
	return (line2);
}
