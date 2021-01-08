/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:58:44 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/08 18:18:17 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int			check_dollar(t_all *all, char **word, int start, int *arr)
{
	int		len;
	char	*tmp;
	char	*tempory;
	int		question_mark;

	tempory = NULL;
	question_mark = 0;
	tmp = ft_strdup((*word));
	if (((*word)[start]) == '?')
	{
		question_mark = 1;
		tempory = ft_itoa(all->exit_status);
	}
	else if (!(tempory = get_env_str(((*word) + start), all)))
		tempory = ft_strdup("");
	free(*word);
	(*word) = ft_calloc(arr[1] - arr[0] + start + ft_strlen(tempory) + 1, 1);
	len = -1;
	while (++len < start)
		(*word)[len] = tmp[len];
	ft_strlcat((*word), tempory, ft_strlen(tempory) + ft_strlen(*word) + 1);
	if (tempory[0] == '\0' || question_mark == 1)
		free(tempory);
	free(tmp);
	return (ft_strlen((*word)));
}

void		search_dollar(char **word, char *str, int **start, int *i)
{
	int		num;
	int		check;

	num = (*start)[0];
	check = *i;
	(*start)[0]++;
	while (str[(*start)[0]] && str[(*start)[0]] != '\'' &&
		str[(*start)[0]] != '\"' && str[(*start)[0]] != ' ' &&
		str[(*start)[0]] != '$' && str[(*start)[0]] != '\\' &&
		str[(*start)[0]] != '=' && str[(*start)[0]] != '|' &&
		str[(*start)[0]] != ']')
	{
		if (str[num] == '$' && ((ft_isdigit(str[num + 1]) &&
			ft_isdigit(str[num + 2])) || str[num + 1] == '?'))
		{
			(*word)[*i] = str[(*start)[0]];
			(*word)[(*i)++] = str[(*start)[0]++];
			break ;
		}
		(*word)[(*i)] = str[(*start)[0]];
		(*start)[0]++;
		(*i)++;
	}
	*i = check;
}

char		*help_variable(t_all *all, char **word, char *str, int **start)
{
	while ((*start)[0] < (*start)[1])
	{
		if (str[(*start)[0]] == '$' && !(all->params.quotes[0] % 2) &&
			(ft_isalnum(str[(*start)[0] + 1]) ||
			str[(*start)[0] + 1] == '_' || str[(*start)[0] + 1] == '?'))
		{
			search_dollar(word, str, start, &(all->params.i));
			all->params.i = check_dollar(all, word,
							all->params.i, all->params.arr);
			(*start)[0]--;
			all->params.i--;
		}
		else if (str[(*start)[0]] == '\\')
		// {
		// 	if (str[(*start)[0] + 1] == 't')
		// 		(*start)[0]++;
		// 	else
				dash(all, word, str, start);
		// }
		else if (str[(*start)[0]] == '\"')
			two_quotes(all, word, str, start);
		else if (str[(*start)[0]] == '\'')
			one_quotes(all, word, str, start);
		else
			(*word)[all->params.i] = str[(*start)[0]];
		(*start)[0]++;
		all->params.i++;
	}
	return (*word);
}

char		*search_variable(t_all *all, char **word, char *str, int **start)
{
	char *line;

	initial_params(all, start);
	line = help_variable(all, word, str, start);
	free_params(all);
	return (str);
}
