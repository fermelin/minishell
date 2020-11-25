/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:26:13 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/25 18:05:42 by fermelin         ###   ########.fr       */
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

void	ctrl_c_handler(int signum)
{
	signum = 0;
	ft_putstr_fd("\b\b  \n> \033[1;35m$\033[0m ", 1);
}

// void	get_more_args(t_all *all)
// {
// 	char	*line;

// 	while (get_next_line(0, &line) != -1)
// 	{
// 		ft_putendl_fd("pipe> ", 1);

// 	}

// }

int		choose_command(t_all *all)
{

	if (all->data->args[0] && ft_strncmp("cd", all->data->args[0], 3) == 0)
		all->exit_status = ft_cd(all->data->args[1], all);
	else if (all->data->args[0] && ft_strncmp("pwd", all->data->args[0], 4) == 0)
		all->exit_status = ft_pwd();
	else if (all->data->args[0] && ft_strncmp("env", all->data->args[0], 4) == 0)
		all->exit_status = ft_env(all);
	else if (all->data->args[0] && ft_strncmp("unset", all->data->args[0], 6) == 0)
		all->exit_status = ft_unset(all, &(all->data->args[1]));
	else if (all->data->args[0] && ft_strncmp("export", all->data->args[0], 7) == 0)
		all->exit_status = ft_export(all, all->data->args + 1);
	else if (all->data->args[0] && ft_strncmp("stat", all->data->args[0], 5) == 0)
		all->exit_status = stat_test(&(all->data->args[1]));
	else if (all->data->args[0] && ft_strncmp("q", all->data->args[0], 2) == 0)
		return (0);
	else
		all->exit_status = exec_cmds(all, all->data->args);
	return (1);
}

int		execution(t_all *all)
{
	while (all->data)			//I could use automatic variable and not save the head
	{
		open_pipe_write_and_close_read(all);
		if (all->data->red_to == 1 || all->data->doub_red_to == 1)
			output_to_file(all);
		else if (all->data->red_from == 1)
			input_from_file(all);
		if (choose_command(all) == 0)
			return (0);
		close_file_or_pipe_read(all);
		all->data = all->data->next;
	}
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	t_all all;

	all.exit_status = 0;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_c_handler);
	if (argc != 1 || !argv)
	{
		ft_putendl_fd("No parameters needed", 2);
		return (-1);
	}
	envp_saving(envp, &all);
	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	parser(&all);
	return (0);
}
