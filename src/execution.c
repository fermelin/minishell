/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:48:33 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/27 16:40:41 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		choose_command(t_all *all)
{

	if (ft_strncmp("cd", all->data->args[0], 3) == 0)
		all->exit_status = ft_cd(all->data->args[1], all);
	else if (ft_strncmp("pwd", all->data->args[0], 4) == 0)
		all->exit_status = ft_pwd();
	else if (ft_strncmp("env", all->data->args[0], 4) == 0)
		all->exit_status = ft_env(all);
	else if (ft_strncmp("unset", all->data->args[0], 6) == 0)
		all->exit_status = ft_unset(all, &(all->data->args[1]));
	else if (ft_strncmp("export", all->data->args[0], 7) == 0)
		all->exit_status = ft_export(all, all->data->args + 1);
	else if (ft_strncmp("stat", all->data->args[0], 5) == 0)		//to delete to delete to delete to delete to delete 
		all->exit_status = stat_test(&(all->data->args[1]));
	else if (ft_strncmp("echo", all->data->args[0], 5) == 0)
		all->exit_status = ft_echo(all->data->args + 1);
	else if (ft_strncmp("q", all->data->args[0], 2) == 0)
		return (0);
	else if (all->data->args && *all->data->args)
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
		if (all->data->args && *all->data->args && choose_command(all) == 0)
			return (0);
		close_file_or_pipe_read(all);
		all->data = all->data->next;
	}
	return (1);
}