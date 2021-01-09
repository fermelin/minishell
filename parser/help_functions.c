/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:39:33 by gevelynn          #+#    #+#             */
/*   Updated: 2021/01/09 15:56:11 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	help_arguments(t_all *all, char **str, int **arr, t_list **new)
{
	syntax_check(all, *str, arr, new);
	while ((*str)[(*arr)[1]] == ' ' || (*str)[(*arr)[1]] == '\t')
	{
		(*arr)[1]++;
		(*arr)[0] = (*arr)[1];
	}
	(*arr)[1] = (*arr)[0] - 1;
}

char	*help_variable(t_all *all, char **word, char *str, int **start)
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
			dash(all, word, str, start);
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
