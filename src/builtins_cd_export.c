/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:09:13 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/28 15:59:02 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static	void	env_vars_sort(t_all *all, int **mass)
{
	int		i;
	size_t	len;
	int		tmp;

	i = 0;
	while (i < (int)all->env_amount - 2)
	{
		len = ft_strlen(all->env_vars[(*mass)[i]]) + 1;
		if (ft_strncmp(all->env_vars[(*mass)[i]], all->env_vars[(*mass)[i + 1]], len) > 0)
		{
			tmp = (*mass)[i + 1];
			(*mass)[i + 1] = (*mass)[i];
			(*mass)[i] = tmp;
			i = -1;
		}
		i++;
	}
}

static	int	export_without_args(t_all *all)
{
	int		*mass;
	size_t	i;

	if (!(mass = (int *)malloc(sizeof(int) * all->env_amount + 1)))
		return (-1);
	i = 0;
	while (i < all->env_amount)
	{
		mass[i] = i;
		i++;
	}
	env_vars_sort(all, &mass);
	i = 0;
	while (i < all->env_amount - 1)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(all->env_vars[mass[i]], 1);
		i++;
	}
	free(mass);
	return (0);
}

static	int	add_empty_line_to_env(t_all *all)
{
	char	**new_env_vars;
	size_t	i;

	all->env_amount++;
	i = 0;
	if (!(new_env_vars = (char **)malloc(sizeof(char *) * (all->env_amount + 1))))
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

static	int		edit_or_add_env_line(char *key, char *value, t_all *all)
{
	int	line_nbr;

	if (ft_strncmp("_=", key, 3) != 0)
	{
		if ((line_nbr = get_env_line_nbr(key, all)) != -1)
		{
			free(all->env_vars[line_nbr]); 					//maybe it is bad
			all->env_vars[line_nbr] = ft_strjoin(key, value);
		}
		else
		{
			if (add_empty_line_to_env(all) == -1)
				return (1);
			all->env_vars[all->env_amount - 2] = ft_strjoin(key, value);
		}
	}
	return (0);
}

int		ft_export(t_all *all, char **args)	//to handle bad symbols
{
	char	*equal_sign_ptr;
	size_t	i;
	int		shift;
	char	*key;

	i = 0;
	if ((!args || !(*args)) && export_without_args(all) == -1)
		return (1);
	else
	while (args[i])
	{
		if ((equal_sign_ptr = ft_strchr(args[i], '=')) && equal_sign_ptr != args[i])
		{
			shift = equal_sign_ptr - args[i] + 1;
			if (!(key = (char *)malloc(sizeof(char) * (shift + 1))))
				return (1);
			ft_strlcpy(key, args[i], shift + 1);
			edit_or_add_env_line(key, &(args[i][shift]), all);	//to do key and value validation before this 
			free(key);
		}
		i++;
	}
	return (0);
}

int			ft_cd(char *path, t_all *all)
{
	int		line_nbr;
	char	*cwd;
	char	*oldpwd;

	if ((!path || !(*path) || ft_strncmp("~", path, 2) == 0) &&
		(line_nbr = get_env_line_nbr("HOME=", all)) != -1)
		path = all->env_vars[line_nbr] + 5;
	if (path && chdir(path) == -1)
	{
		print_error("cd", path, strerror(errno));
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if ((line_nbr = get_env_line_nbr("PWD=", all)) != -1)
	{
		oldpwd = all->env_vars[line_nbr];
		edit_or_add_env_line("OLDPWD=", oldpwd + 4, all);
	}
	else
		edit_or_add_env_line("OLDPWD=", cwd, all);
	edit_or_add_env_line("PWD=", cwd, all);
	free(cwd);
	return (0);
}
