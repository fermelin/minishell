/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:10:21 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/28 13:44:07 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef ANTON

int		is_redirection(char *sign)
{
	if (ft_strncmp(">", sign, 2) == 0)
		return (1);
	else if (ft_strncmp(">>", sign, 2) == 0)
		return (2);
	else if (ft_strncmp("<", sign, 2) == 0)
		return (3);
	return (0);
}

void	parser_to_list(t_all *all, char **splited)
{
	int	i;
	int	j;
	t_data	*beginning;
	char	**beginning_s;
	int		is_pipe_behind;

	beginning = all->data;
	beginning_s = splited;
	is_pipe_behind = 0;
	while (splited)
	{
		i = 0;
		j = 0;
		while (splited[i] && (ft_strncmp("|", splited[i], 2)) != 0 && (ft_strncmp(";", splited[i], 2)) != 0 && !is_redirection(splited[i]))
			i++;
		if (!(all->data->args = (char**)malloc(sizeof(char *) * (i + 1))))
			return ;
		while (i > 0)
		{
			all->data->args[j] = ft_strdup(*splited);
			splited++;
			j++;
			i--;
		}
		all->data->args[j] = NULL;
		if (is_pipe_behind == 1)
			all->data->pipe_behind = 1;
		if ((*splited) && is_redirection(*splited))
		{
			if (is_redirection(*splited) == 1)
				all->data->red_to = 1;
			else if (is_redirection(*splited) == 2)
				all->data->doub_red_to = 1;
			else if (is_redirection(*splited) == 3)
				all->data->red_from = 1;
			splited++;
			all->data->file_name = ft_strdup(*splited);
			splited++;
		}
		if (!(*splited))
			break ;
		if ((ft_strncmp("|", *splited, 2) == 0) || (ft_strncmp(";", *splited, 2) == 0))
		{
			if (ft_strncmp("|", *splited, 2) == 0)
			{
				all->data->pipe = 1;
				is_pipe_behind = 1;
			}
			else
				is_pipe_behind = 0;
			splited++;
		}
		if (!(all->data->next = p_lstnew()))
			return ;
		all->data = all->data->next;
	}
	all->data = beginning;
	splited = beginning_s;
}

void	my_parser(char *line, t_all *all)
{
	char	**splited;

		if ((splited = ft_split(line, ' ')))
		{
			all->data = p_lstnew();
			all->head = all->data;
			parser_to_list(all, splited);
		}

}

#endif