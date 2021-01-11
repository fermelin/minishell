/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:43:24 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/11 12:52:32 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	close_write_and_open_read(t_all *all)
{
	dup2(all->save1, 1);
	if (close(all->save1) == -1)
		print_error("close", "save1", strerror(errno));
	all->save0 = dup(0);
	if (close(0) == -1)
		print_error("close", "0", strerror(errno));
	dup2(all->fildes1[0], 0);
	if (close(all->fildes1[0]) == -1)
		print_error("close", "fildes1[0] 2", strerror(errno));
}

void			open_pipe_write_and_close_read(t_all *all)
{
	if (all->data->pipe == 1 && all->data->pipe_behind == 0)
	{
		pipe(all->fildes1);
		all->save1 = dup(1);
		if (close(1) == -1)
			print_error("close", "1", strerror(errno));
		dup2(all->fildes1[1], 1);
		if (close(all->fildes1[1]) == -1)
			print_error("close", "fildes1[1] 2", strerror(errno));
	}
	else if (all->data->pipe_behind == 1)
		close_write_and_open_read(all);
	if (all->data->pipe == 1 && all->data->pipe_behind == 1)
	{
		pipe(all->fildes2);
		all->save1 = dup(1);
		if (close(1) == -1)
			print_error("close", "1", strerror(errno));
		dup2(all->fildes2[1], 1);
		if (close(all->fildes2[1]) == -1)
			print_error("close", "fildes2[1] 1", strerror(errno));
	}
}

void			close_file(t_all *all, int is_error_while_open)
{
	if (all->data->redir == 3)
	{
		if (is_error_while_open != -1)
		{
			dup2(all->save0_red, 0);
			if (close(all->save0_red) == -1)
				print_error("close", "save0 while red_from", strerror(errno));
		}
	}
	else if (all->data->redir)
	{
		dup2(all->save1_red, 1);
		if (close(all->save1_red) == -1)
			print_error("close", "save1 while red_to", strerror(errno));
	}
}

void			close_pipe_read(t_all *all)
{
	if (all->data->pipe_behind == 1)
	{
		dup2(all->save0, 0);
		if (close(all->save0) == -1)
			print_error("close", "save0", strerror(errno));
	}
	if (all->data->pipe == 1 && all->data->pipe_behind == 1)
	{
		all->fildes1[0] = all->fildes2[0];
		all->fildes1[1] = all->fildes2[1];
	}
}
