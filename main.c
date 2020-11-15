/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:26:13 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/13 19:26:16 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_all *all)
{
	int i;

	i = 0;
	while (all->env_vars[i])
		ft_putendl_fd(all->env_vars[i++], 1);

}

// int		ft_echo(char *str, t_all *all)
// {
// 	ft_putstr_fd(1, )
// }

int		get_env_line(char *to_find, t_all *all)
{
	int i;
	int len;

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

int		edit_or_add_env_line(char *key, char *value, t_all *all)
{
	int		line_nbr;
	char	*old_line;
	char	*tmp;

	if (!ft_strchr(key, '='))
		return (0);			//to do nothing
	if ((line_nbr = get_env_line(key, all)) != -1)
	{
		free(all->env_vars[line_nbr]); 					//shit
		all->env_vars[line_nbr] = ft_strjoin(key, value);
		free(value);
	}
	// else
	// {

	// }
	return (0);

}

int		ft_cd(char *path, t_all *all)
{
	int		i;
	int		line_nbr;
	char	*cwd;
	char	*pwd;
	char	*oldpwd;

	i = 0;
	if (chdir(path) == -1)
		return (errno);		//error handling
	// if ((line_nbr = get_env_line("PWD=", all)) != -1)
	// 	oldpwd = all->env_vars[line_nbr];
	// edit_or_add_env_line("OLDPWD=", oldpwd + 7, all);
	// edit_or_add_env_line("PWD=", cwd = getcwd(NULL, 0), all);
	// free(cwd);

	// if ((line_nbr = get_env_line("PWD=", all)) != -1)
	// {
	// 	oldpwd = all->env_vars[line_nbr];
	// 	all->env_vars[line_nbr] = getcwd(NULL, 0);
	// 	all->env_vars[line_nbr] = ft_strjoin(tmp, path);
	// 	free(tmp);
	// }
	// else
	// {

	// }
	return (0); //error
}

int		ft_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}

void	free_ptrs_array(char **ptr_array)
{
	int i;

	i = 0;
	while (ptr_array[i])
	{
		free(ptr_array[i]);
		ptr_array[i] = NULL;
		i++;
	}
	free(ptr_array);
}

void	envp_saving(char **envp, t_all *all)
{
	int		i;
	char	*str;
	int		len;

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

int		main(int argc, char **argv, char **envp)
{
	char *line;
	t_all all;
	int i;
	char **splited;

	i = 0;
	envp_saving(envp, &all);
	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	while (get_next_line(0, &line) > 0)
	{
		splited = ft_split(line, ' ');
		if (ft_strncmp("cd", line, 2) == 0)
			ft_cd(splited[1], &all);
		else if (ft_strncmp("pwd", line, 3) == 0)
			ft_pwd();
		else if (ft_strncmp("env", line, 3) == 0)
			ft_env(&all);
		else
			break;
		free(line);
		line = NULL;
		free_ptrs_array(splited);
		ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	}
	return (0);
}
