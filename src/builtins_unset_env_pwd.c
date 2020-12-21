/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset_env_pwd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:21:15 by fermelin          #+#    #+#             */
/*   Updated: 2020/12/21 20:57:06 by fermelin         ###   ########.fr       */
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

int		unset_arg_validation(char *arg, int *exit_status)
{
	size_t i;

	i = 0;
	while (arg[i] && ft_isalnum(arg[i]))
		i++;
	if (arg[i] == '\0' && i != 0)
		return (0);
	print_unset_error("unset", arg, NOT_VALID_ID);
	*exit_status = 1;
	return (1);
}

int		ft_unset(t_all *all, char **args)
{
	size_t i;
	size_t j;
	size_t len;
	int		exit_status;

	i = 0;
	exit_status = 0;
	if (!args || !(*all->env_vars))
		return (0);
	while (args[i])
	{
		j = 0;
		len = ft_strlen(args[i]);
		if (unset_arg_validation(args[i], &exit_status) == 0)
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
	return (exit_status);
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
