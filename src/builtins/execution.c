/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:48:33 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/11 12:51:29 by fermelin         ###   ########.fr       */
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
	else if (ft_strncmp("echo", all->data->args[0], 5) == 0)
		all->exit_status = ft_echo(all->data->args + 1);
	else if (ft_strncmp("exit", all->data->args[0], 5) == 0)
		all->exit_status = ft_exit(all->data->args + 1, all);
	else if (all->data->args && *all->data->args)
		all->exit_status = exec_cmds(all, all->data->args);
	return (1);
}

int		what_redirection(char *sign)
{
	if (ft_strncmp(">", sign, 2) == 0)
		return (1);
	else if (ft_strncmp(">>", sign, 3) == 0)
		return (2);
	else if (ft_strncmp("<", sign, 2) == 0)
		return (3);
	return (0);
}

int		setting_pipes_and_redirections(t_all *all)
{
	size_t i;

	i = 0;
	open_pipe_write_and_close_read(all);
	if (all->data->redir_array)
		while (all->data->redir_array[i])
		{
			if ((all->data->redir =
				what_redirection(all->data->redir_array[i])))
			{
				i++;
				if (all->data->redir == 3)
				{
					if (input_from_file(all, all->data->redir_array[i]) == -1)
						return (-1);
				}
				else
					output_to_file(all, all->data->redir_array[i]);
			}
			i++;
			if (all->data->redir_array[i])
				close_file(all, 0);
		}
	return (0);
}

void	execution(t_all *all)
{
	t_data	*head;
	int		is_error_while_open;

	head = all->data;
	while (all->data)
	{
		is_error_while_open = 0;
		if (all->data->redir || all->data->pipe || all->data->pipe_behind)
			is_error_while_open = setting_pipes_and_redirections(all);
		if (all->data->args && *all->data->args && is_error_while_open != -1)
			choose_command(all);
		close_pipe_read(all);
		close_file(all, is_error_while_open);
		all->data = all->data->next;
	}
	p_lstclear(&head);
}
