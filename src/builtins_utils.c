/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:37:00 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/04 14:01:34 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ctrl_c_handler(int signum)
{
	signum = 0;
	ft_putstr_fd("\b\b  \n> \033[1;35m$\033[0m ", 2);
}

void		free_ptrs_array(char **ptr_array)
{
	size_t i;

	i = 0;
	if (ptr_array)
	{
		while (ptr_array[i])
		{
			free(ptr_array[i]);
			ptr_array[i] = NULL;
			i++;
		}
		free(ptr_array);
	}
}

static	int	add_empty_line_to_env(t_all *all)
{
	char	**new_env_vars;
	size_t	i;

	all->env_amount++;
	i = 0;
	if (!(new_env_vars = (char **)malloc(sizeof(char *) *
		(all->env_amount + 1))))
		return (-1);
	while (i < all->env_amount - 2)
	{
		new_env_vars[i] = all->env_vars[i];
		i++;
	}
	new_env_vars[i + 1] = all->env_vars[i];
	new_env_vars[all->env_amount] = NULL;
	free(all->env_vars);
	all->env_vars = new_env_vars;
	return (0);
}

int			edit_or_add_env_line(char *key, char *value, t_all *all)
{
	int	line_nbr;

	if (ft_strncmp("_=", key, 3) != 0)
	{
		if ((line_nbr = get_env_line_nbr(key, all)) != -1)
		{
			free(all->env_vars[line_nbr]);
			all->env_vars[line_nbr] = ft_strjoin(key, value);
		}
		else
		{
			if (add_empty_line_to_env(all) == -1)
				return (-1);
			all->env_vars[all->env_amount - 2] = ft_strjoin(key, value);
		}
	}
	return (0);
}
