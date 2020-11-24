/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:43:24 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/24 18:34:09 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_pipe(char **splited)		//to delete to delete to delete to delete to delete
{
	int i;

	i = 0;
	while (splited[i])
	{
		if (ft_strncmp("|", splited[i], 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	parser_to_list(t_all *all, char **splited)
{
	int	i;
	int	j;
	t_data	*beginning;
	char	**beginning_s;

	beginning = all->data;
	beginning_s = splited;
	while (splited)
	{
		i = 0;
		j = 0;
		while (splited[i] && (ft_strncmp("|", splited[i], 2)) != 0 && (ft_strncmp(";", splited[i], 2)) != 0)
			i++;
		if (!(all->data->args = (char**)malloc(sizeof(char *) * (i + 1))))
			return ;
		while (i > 0)
		{
			all->data->args[j] = ft_strdup(*splited);
			splited++;
			j++;
			i--;
		}
		all->data->args[j] = NULL;
		if (!(*splited))
			break ;
		if (ft_strncmp("|", *splited, 2) == 0)
		{
			splited++;
			all->data->pipe = 1;
		}
		if (ft_strncmp(";", *splited, 2) == 0)
			splited++;
		if (!(all->data->next = p_lstnew()))
			return ;
		all->data = all->data->next;
	}
	all->data = beginning;
	splited = beginning_s;
	// pipe(fildes);
	// exec_cmds_pipe(all);
	
}

int		child_process_pipe(t_all *all, int fildes, int thread)
{
	char	*path;
	int		execve_ret;
	int		save;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	save = dup(thread);
	close(thread);
	dup2(fildes, thread);
	execve_ret = 0;
	if ((ft_strncmp("./", all->data->args[0], 2)) == 0 ||
		(ft_strncmp("../", all->data->args[0], 3)) == 0 || (ft_strncmp("/", all->data->args[0], 1)) == 0)
		execve_ret = execve(all->data->args[0], all->data->args, all->env_vars);
	else if ((path = find_file_in_path(all->data->args[0], all)))
	{
		execve_ret = execve(path, all->data->args, all->env_vars);
		free(path);
	}
	else
	{
		ft_putstr_fd("msh: command not found: ", 2);
		ft_putendl_fd(all->data->args[0], 2);
	}
	if (execve_ret == -1)
	{
		perror(all->data->args[0]);
		// printf("MY:\n");
		// error_exit("execve");
	}
	dup2(save, thread);
	close(save);
	close(fildes);
	exit(execve_ret);
}


void	exec_cmds_pipe(t_all *all)
{
	int		status;
	int		pid;
	int		pid1;
	int		fildes[2];

	pipe(fildes);
	pid = fork();
	if (pid == 0)
	{
		close(fildes[0]);
		child_process_pipe(all, fildes[1], 1);
	}
	else
	{
		wait(&status);
		close(fildes[1]);
		if (all->data->pipe == 1)
		{
			pid1 = fork();
			if (pid1 == 0)
			{
				close(fildes[1]);
				all->data = all->data->next;
				child_process_pipe(all, fildes[0], 0);
			}
			else
			{
				wait(&status);
				close(fildes[0]);
				close(fildes[1]);
				if (WIFSIGNALED(status))
					all->child_killed = 1;
			}
		}
		// wait(&status);
		if (WIFSIGNALED(status))
			all->child_killed = 1;
	}
}

// void	exec_cmds_pipe(t_all *all)
// {
// 	int		status;
// 	int		pid;
// 	int		pid1;
// 	int		fildes[2];


// 	pid = fork();
// 	pid1 = -2;
// 	if (pid == 0)
// 	{
// 		if (all->data->pipe == 1)
// 		{
// 			pipe(fildes);
// 			// close(fildes[0]);
// 			child_process_pipe(all);
// 			if ((pid1 = fork()) == -1)
// 				return ;
// 		}
// 		if (pid1 == 0)
// 		{
// 			all->data = all->data->next;
// 			child_process_pipe(all);
// 		}
// 		else if (pid1 != -2)
// 		{
// 			wait(&status);
// 			if (WIFSIGNALED(status))
// 				all->child_killed = 1;
// 		}
// 	}
// 	else
// 	{
// 		wait(&status);
// 		if (WIFSIGNALED(status))
// 			all->child_killed = 1;
// 	}
// }








