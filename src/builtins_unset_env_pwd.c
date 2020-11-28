/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset_env_pwd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:21:15 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/28 13:07:25 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	delete_line_from_env(t_all *all, size_t arg_nbr)
{
	char	**new_env_vars;
	size_t	i;
	size_t	j;

	all->env_amount--;
	i = 0;
	j = 0;
	if (!(new_env_vars = (char **)malloc(sizeof(char *) * (all->env_amount + 1))))
		return (-1);	//error handling
	while (all->env_vars[i])
	{
		if (i != arg_nbr)
		{
			new_env_vars[j] = all->env_vars[i];
			j++;
		}
		else
			free(all->env_vars[i]);
		i++;
	}
	new_env_vars[all->env_amount] = NULL;
	free(all->env_vars);
	all->env_vars = new_env_vars;
	return (0);
}

int		ft_unset(t_all *all, char **args)
{
	size_t i;
	size_t j;
	size_t len;

	i = 0;
	if (!args || !(*all->env_vars))
		return (0);
	while (args[i])
	{
		j = 0;
		len = ft_strlen(args[i]);
		while (all->env_vars[j])
		{
			if (all->env_vars[j][len] == '=' && !(*args[i] == '_' && len == 1)
				&& ft_strncmp(args[i], all->env_vars[j], len) == 0)
			{
				if (delete_line_from_env(all, j) == -1)
					return (1);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_env(t_all *all)
{
	size_t i;

	i = 0;
	while (all->env_vars[i])
		ft_putendl_fd(all->env_vars[i++], 1);
	return (0);
}

int			ft_pwd(void)
{
	char *cwd;

	if ((cwd = getcwd(NULL, 0)) == NULL)
		return (1);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}
