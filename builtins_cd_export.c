/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:09:13 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/16 15:09:16 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_env_line(char *to_find, t_all *all)
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

static	void	add_empty_line_to_env(t_all *all)
{
	char	**new_env_vars;
	size_t	i;

	all->env_amount++;
	i = 0;
	if (!(new_env_vars = (char **)malloc(sizeof(char *) * (all->env_amount + 1))))
		return ;	//error handling
	while (i < all->env_amount - 2)
	{
		new_env_vars[i] = all->env_vars[i];
		i++;
	}
	new_env_vars[i + 1] = all->env_vars[i];
	new_env_vars[all->env_amount] = NULL;
	free(all->env_vars);
	all->env_vars = new_env_vars;
}

static	int		edit_or_add_env_line(char *key, char *value, t_all *all)
{
	size_t	line_nbr;

	// if (!ft_strchr(key, '='))
	// 	return (0);			//to do nothing
	if (ft_strncmp("_=", key, 3) != 0)
	{
		if ((line_nbr = get_env_line(key, all)) != -1)
		{
			free(all->env_vars[line_nbr]); 					//maybe it is bad
			all->env_vars[line_nbr] = ft_strjoin(key, value);
		}
		else
		{
			add_empty_line_to_env(all);
			all->env_vars[all->env_amount - 2] = ft_strjoin(key, value);
		}
	}
	return (0);
}

void		ft_export(t_all *all, char **args)	//to handle bad symbols
{
	char	*equal_sign_ptr;
	size_t	i;
	int		shift;
	char	*key;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		if ((equal_sign_ptr = ft_strchr(args[i], '=')) && equal_sign_ptr != args[i])
		{
			shift = equal_sign_ptr - args[i] + 1;
			if (!(key = (char *)malloc(sizeof(char) * (shift + 1))))
				return ;
			ft_strlcpy(key, args[i], shift + 1);
			edit_or_add_env_line(key, &(args[i][shift]), all);	//to do key and value validation before this 
			free(key);
		}
		i++;
	}
}

int			ft_cd(char *path, t_all *all)
{
	size_t	i;
	int		line_nbr;
	char	*cwd;
	char	*oldpwd;

	i = 0;
	if ((!path || !(*path)) && (line_nbr = get_env_line("HOME=", all)) != -1)
		path = all->env_vars[line_nbr] + 5;
	if (path && chdir(path) == -1)
		return (errno);		//error handling
	cwd = getcwd(NULL, 0);
	if ((line_nbr = get_env_line("PWD=", all)) != -1)
	{
		oldpwd = all->env_vars[line_nbr];
		edit_or_add_env_line("OLDPWD=", oldpwd + 4, all);
	}
	else
		edit_or_add_env_line("OLDPWD=", cwd, all);
	edit_or_add_env_line("PWD=", cwd, all);
	free(cwd);
	return (0); //error
}