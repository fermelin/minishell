/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:26:13 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/20 18:33:26 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		ft_echo(char *str, t_all *all)
// {
// 	if (!flag_n)
// 		ft_putendl_fd(str, 1);
// 	else
// 		ft_putstr_fd(str, 1);
// }

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

// char	*get_env_str(char *key, t_all *all)	//for $<env_var>
// {
// 	int	nbr;
// 	int	key_len;

// 	if (!key || !(*key) || (nbr = get_env_line_nbr(key, all)) == -1)
// 		return (NULL);
// 	key_len = ft_strlen(key);
// 	if (all->env_vars[nbr][key_len] != '=')
// 		return (NULL);
// 	return (&(all->env_vars[nbr][key_len + 1]));
// }

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

void	ctrl_c_handler(int signum)
{
	signum = 0;
	// printf("ctrl + d pressed, sig num is %d\n", signum);
	// int fd;
	// int save;

	// save = dup(0);
	// close(0);

	ft_putstr_fd("\n> \033[1;35m$\033[0m ", 1);
	// dup2(save, 0);
	// close(save);
	// exit(0);
}

void	parser(t_all *all)
{
	char *line;
	char **splited;
	

	while (get_next_line(0, &line) > 0)
	{
		if ((splited = ft_split(line, ' ')))
		{
			if (ft_strncmp("cd", splited[0], 3) == 0)
				ft_cd(splited[1], all);
			else if (ft_strncmp("pwd", splited[0], 4) == 0)
				ft_pwd();
			else if (ft_strncmp("env", splited[0], 4) == 0)
				ft_env(all);
			else if (ft_strncmp("unset", splited[0], 6) == 0)
				ft_unset(all, &(splited[1]));
			else if (ft_strncmp("export", splited[0], 7) == 0)
				ft_export(all, splited + 1);
			else if (ft_strncmp("stat", splited[0], 5) == 0)
				stat_test(&(splited[1]));
			else if (ft_strncmp("q", splited[0], 2) == 0)
				break;
			else
				exec_cmds(all, splited);
		}
		free(line);
		line = NULL;
		free_ptrs_array(splited);
		if (all->child_killed != 1)
			ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
		all->child_killed = 0;
	}
	ft_putendl_fd("exit", 1);
}

int		main(int argc, char **argv, char **envp)
{
	t_all all;

	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_c_handler);
	if (argc != 1 || !argv)
	{
		ft_putendl_fd("No parameters needed", 2);
		return (-1);
	}
	
	// signal(SIGINT, ctrl_c_handler);
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, ctrl_d_handler);
	// signal(SIGINT, ctrl_d_handler);

	envp_saving(envp, &all);
	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	parser(&all);
	return (0);
}
