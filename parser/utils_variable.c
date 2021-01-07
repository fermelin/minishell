/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 20:57:23 by gevelynn          #+#    #+#             */
/*   Updated: 2021/01/07 14:19:43 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_params(t_all *all)
{
	free(all->params.quotes);
	free(all->params.arr);
}

void	initial_params(t_all *all, int **start)
{
	all->params.quotes = malloc(sizeof(int) * 2);
	all->params.arr = malloc(sizeof(int) * 2);
	all->params.arr[0] = (*start)[0];
	all->params.arr[1] = (*start)[1];
	all->params.quotes[0] = 0;
	all->params.quotes[1] = 0;
	all->params.i = 0;
}

void	dash(t_all *all, char **word, char *str, int **start)
{
	if (!(all->params.quotes[0] % 2) && !(all->params.quotes[1] % 2))
		(*word)[all->params.i] = str[++(*start)[0]];
	else if (all->params.quotes[0] % 2 && !(all->params.quotes[1] % 2))
		(*word)[all->params.i] = str[(*start)[0]];
	else if (!(all->params.quotes[0] % 2) && all->params.quotes[1] % 2)
	{
		if (str[(*start)[0] + 1] == '$' || str[(*start)[0] + 1] == '\\' ||
			str[(*start)[0] + 1] == '\"')
			(*word)[all->params.i] = str[++(*start)[0]];
		else
			(*word)[all->params.i] = str[(*start)[0]];
	}
}

void	two_quotes(t_all *all, char **word, char *str, int **start)
{
	all->params.quotes[1]++;
	if (all->params.quotes[0] % 2)
	{
		(*word)[all->params.i] = str[(*start)[0]];
		all->params.quotes[1]++;
	}
	else if (!(all->params.quotes[0] % 2))
		all->params.i--;
}

void	one_quotes(t_all *all, char **word, char *str, int **start)
{
	all->params.quotes[0]++;
	if (all->params.quotes[1] % 2)
	{
		(*word)[all->params.i] = str[(*start)[0]];
		all->params.quotes[0]++;
	}
	else if (!(all->params.quotes[1] % 2))
		all->params.i--;
}
