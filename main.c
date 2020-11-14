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


int		ft_echo(char *str, t_all *all)
{
	ft_putstr_fd(1, )
}	

int		get_env_var_line(char *to_find, t_all *all)
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

int		ft_cd(char *path)//, t_all *all)
{
	int i;
	int line_nbr;
	char *tmp;

	i = 0;
	chdir(path);
	// if ((line_nbr = get_env_var_line("PWD=", all)) != -1)
	// {
	// 	tmp = all->env_vars[line_nbr];
	// 	all->env_vars[line_nbr] = ft_strjoin(tmp, path);
	// 	free(tmp);
	// }
	return (0); //error
}



int		ft_pwd(void)
{
	char *cwd_ret;

	cwd_ret = getcwd(NULL, 0);
	ft_putendl_fd(cwd_ret, 1);
	free(cwd_ret);
	return (0);
}

void	free_ptr_array(char **ptr_array)
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
			return (free_ptr_array(all->env_vars));
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
	while (all.env_vars[i])
	{
		printf("%s\n", all.env_vars[i]);
		i++;
	}
	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	while (get_next_line(0, &line) > 0)
	{
		splited = ft_split(line, ' ');
		if (ft_strncmp("cd", line, 2) == 0)
			ft_cd(splited[1]);//, &all);
		else if (ft_strncmp("pwd", line, 3) == 0)
			ft_pwd();
		else
			break;
		free(line);
		line = NULL;
		free_ptr_array(splited);
		ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	}
	return (0);
}

