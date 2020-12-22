/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:21:33 by fermelin          #+#    #+#             */
/*   Updated: 2020/12/22 17:46:28 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_file_exec_error(char *path)
// {
	
// }

int		is_exec_file_correct(t_all *all, char **path, char **argv)
{
	struct stat buf;

	if ((ft_strncmp("./", argv[0], 2)) == 0 ||
		(ft_strncmp("../", argv[0], 3)) == 0 || (ft_strncmp("/", argv[0], 1)) == 0)
		*path = argv[0];
	else if (find_file_in_path(argv[0], path, all) == 1)
		;
	// else
	// {
	// 	print_error(argv[0], "", CMD_NOT_FOUND);
	// 	exit (127);
	// }
	if (stat(*path, &buf) == 0)
	{
		if ((buf.st_mode & S_IFDIR) == S_IFDIR)
			print_error(*path, "", IS_A_DIR);
		else if ((buf.st_mode & S_IXUSR) != S_IXUSR)
		{
			errno = EACCES;
			print_error(*path, "", strerror(errno));
		}
		else
			return (1);
		exit (126);
	}
	else
	{
		print_error(argv[0], "", CMD_NOT_FOUND);
		exit (127);
	}
}
int		child_process(t_all *all, char **argv)
{
	char	*path;
	int		execve_ret;
	int		error_handling_fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve_ret = 0;
	error_handling_fd = 0;
		// if ((ft_strncmp("./", argv[0], 2)) == 0 ||
		// 	(ft_strncmp("../", argv[0], 3)) == 0 || (ft_strncmp("/", argv[0], 1)) == 0)
		// {
		// 	execve_ret = execve(argv[0], argv, all->env_vars);
		// 	path = argv[0];
		// }
		// else if (find_file_in_path(argv[0], &path, all) == 1)
		// 	execve_ret = execve(path, argv, all->env_vars);
		// else
		// {
		// 	print_error(argv[0], "", CMD_NOT_FOUND);
		// 	exit (127);
		// }

		// print_file_exec_error(path);
		
		// printf("%d\n", errno);
	if (is_exec_file_correct(all, &path, argv) == 1)
		execve_ret = execve(path, argv, all->env_vars);
	// else
	// {
	// 	print_error(argv[0], "", CMD_NOT_FOUND);
	// 	exit (127);
	// }
	exit (0);
		// if ((error_handling_fd = open(argv[0], O_RDWR)) == -1)
		// 	;
	// printf("%d\n", execve_ret);
	// if (errno == 21)
	// 	print_error(argv[0], "", IS_A_DIR);
	// else
	// 	print_error(argv[0], "", strerror(errno));
	// 	// free(path);
	// 	exit (126);
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
		else if (stat_ret == 0)
		{
			printf("file %d exists!!!\n", i);
			if ((buf.st_mode & S_IFDIR) == S_IFDIR)
				printf("this is a directory!!!\n");
		}
		i++;
	}
	return (0);
}

int		find_file_in_path(char	*file_name, char **path, t_all *all)
{
	char	*path_slashed;
	char	**splited_path;
	int		env_line;
	int		i;
	struct stat buf;

	i = 0;
	if ((env_line = get_env_line_nbr("PATH=", all)) == -1)
		return (0);
	splited_path = ft_split(all->env_vars[env_line] + 5, ':');
	while (splited_path[i])
	{
		path_slashed = ft_strjoin(splited_path[i], "/");
		*path = ft_strjoin(path_slashed, file_name);
		free(path_slashed);
		if (stat(*path, &buf) == 0)
		{
			free_ptrs_array(splited_path);
			return (1);
		}
		free(*path);
		i++;
	}
	free_ptrs_array(splited_path);
	return (0);
}
