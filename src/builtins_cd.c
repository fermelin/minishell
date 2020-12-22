/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:09:13 by fermelin          #+#    #+#             */
/*   Updated: 2020/12/22 11:42:46 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_cd(char *path, t_all *all)
{
	int		line_nbr;
	char	*cwd;
	char	*oldpwd;

	if ((!path || !(*path) || ft_strncmp("~", path, 2) == 0) &&
		(line_nbr = get_env_line_nbr("HOME=", all)) != -1)
		path = all->env_vars[line_nbr] + 5;
	if (path && chdir(path) == -1 && (*path))
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
		edit_or_add_env_line("OLDPWD=", "", all);
	edit_or_add_env_line("PWD=", cwd, all);
	free(cwd);
	return (0);
}
