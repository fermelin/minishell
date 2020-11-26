/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:29:03 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/25 18:50:07 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_handler(int signum)
{
	signum = 0;
	ft_putstr_fd("\b\b  \n> \033[1;35m$\033[0m ", 1);
}

void	free_ptrs_array(char **ptr_array)
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

int		get_env_line_nbr(char *to_find, t_all *all)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(to_find);
	while (all->env_vars[i])
	{
		if (ft_strncmp(to_find, all->env_vars[i], len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	envp_saving(char **envp, t_all *all)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (envp[i])
		i++;
	all->env_amount = i;
	if (!(all->env_vars = (char **)malloc(sizeof(char *) * (i + 1))))
		return ;
	i = 0;
	while (envp[i])
	{
		len = ft_strlen(envp[i]);
		if (!(all->env_vars[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (free_ptrs_array(all->env_vars));
		ft_strlcpy(all->env_vars[i], envp[i], len + 1);
		i++;
	}
	all->env_vars[i] = NULL;
}

char	*get_env_str(char *key, t_all *all)
{
	int	nbr;
	int	key_len;

	if (!key || !(*key) || (nbr = get_env_line_nbr(key, all)) == -1)
		return (NULL);
	key_len = ft_strlen(key);
	if (all->env_vars[nbr][key_len] != '=')
		return (NULL);
	return (&(all->env_vars[nbr][key_len + 1]));
}