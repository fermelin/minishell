/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:21:33 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/19 20:24:16 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ctrl_backslash_handler(int signum)
// {

// }

// static void	ctrl_c_handler_child(int signum)
// {
// 	printf("CHILD receives signal %d\n", signum);
// 	exit(0);
// }

void	exec_cmds(t_all *all, char **argv)
{
	int		status;
	int		execve_ret;
	char	*path;
	int		pid;
	// void	*sig_ret;
	// signal(SIGINT, )
	pid = fork();
	if (pid == 0)
	{
		// signal(SIGINT, ctrl_c_handler_child);
		signal(SIGINT, SIG_DFL);
		// printf("sig_ret is %s\n", sig_ret);
		execve_ret = 0;
		if ((ft_strncmp("./", argv[0], 2)) == 0 ||
			(ft_strncmp("../", argv[0], 3)) == 0 || (ft_strncmp("/", argv[0], 1)) == 0)
			execve_ret = execve(argv[0], argv, all->env_vars);
		else if ((path = find_file_in_path(argv[0], all)))
		{
			execve_ret = execve(path, argv, all->env_vars);
			free(path);
		}
		else
		{
			ft_putstr_fd("msh: command not found: ", 2);
			ft_putendl_fd(argv[0], 2);
		}
		if (execve_ret == -1)
			perror(argv[0]);
		exit(execve_ret);
	}
	else
	{
		// signal(SIGINT, SIG_IGN);
		wait(&status);
		if (WIFSIGNALED(status))
			all->child_killed = 1;
	}
}

void	stat_test(char **file_names)
{
	struct stat buf;
	int		stat_ret;
	int		i;

	i = 0;
	while (file_names[i])
	{
		stat_ret = stat(file_names[i], &buf);
		if (stat_ret == -1)
			printf("file %d not found\n", i);
		if (stat_ret == 0)
			printf("file %d exists!!!\n", i);
		i++;
	}
}
// void (*signal(int sig, void (*func)(int)))(int)

char	*find_file_in_path(char	*file_name, t_all *all)
{
	char	*path_slashed;
	char	**splited_path;
	char	*absolute_filename;
	int		env_line;
	int		i;
	struct stat buf;
	int		stat_ret;

	i = 0;
	if ((env_line = get_env_line("PATH=", all)) == -1)
		return (NULL);
	splited_path = ft_split(all->env_vars[env_line] + 5, ':');
	while (splited_path[i])
	{
		path_slashed = ft_strjoin(splited_path[i], "/");
		absolute_filename = ft_strjoin(path_slashed, file_name);
		free(path_slashed);
		stat_ret = stat(absolute_filename, &buf);
		if (stat_ret == 0)
			return (absolute_filename);
		free(absolute_filename);
		i++;
	}
	free_ptrs_array(splited_path);
	return (NULL);
}




























