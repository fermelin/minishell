/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:21:33 by fermelin          #+#    #+#             */
/*   Updated: 2020/12/21 22:08:19 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		child_process(t_all *all, char **argv)
{
	char	*path;
	int		execve_ret;
	int		error_handling_fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
			print_error(argv[0], "", CMD_NOT_FOUND);
			exit (127);
		}
		if ((error_handling_fd = open(argv[0], O_RDWR)) == -1)
			;
	// printf("%d\n", execve_ret);
	if (errno == 21)
		print_error(argv[0], "", IS_A_DIR);
	else
		print_error(argv[0], "", strerror(errno));
		exit (126);
	// printf("%d\n", errno);
		// exit (0);

	// print_error(argv[0], "", CMD_NOT_FOUND);
	// exit (127);
}

int		exec_cmds(t_all *all, char **argv)
{
	int		status;
	int		pid;

	pid = fork();
	if (pid == 0)
		child_process(all, argv);
	else
	{
		wait(&status);
		// waitpid(pid, &status, WNOHANG | WUNTRACED);
		if (WIFSIGNALED(status))	// change it to SIGCHLD
			all->child_killed = 1;
	}
	return (WEXITSTATUS(status));
}

int		stat_test(char **file_names)		//to delete to delete to delete to delete to delete to delete to delete to delete 
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
	return (0);
}

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
	if ((env_line = get_env_line_nbr("PATH=", all)) == -1)
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
