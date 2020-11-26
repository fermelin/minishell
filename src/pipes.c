/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:43:24 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/26 14:01:53 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_write_and_open_read(t_all *all)
{
	dup2(all->save1, 1);
	if (close(all->save1) == -1)
		error_message("close save1");	//close write
	all->save0 = dup(0);
	if (close(0) == -1)
		error_message("close 0");
	dup2(all->fildes1[0], 0);	//open read
	if (close(all->fildes1[0]) == -1)
		error_message("close fildes1[0] 2");
}

void	open_pipe_write_and_close_read(t_all *all)
{
	if (all->data->pipe == 1 && all->data->pipe_behind == 0)
	{
		pipe(all->fildes1);
		all->save1 = dup(1);
		if (close(1) == -1)
			error_message("close 1");
		dup2(all->fildes1[1], 1);	//open write
		if (close(all->fildes1[1]) == -1)
			error_message("close fildes1[1] 2");
	}
	else if (all->data->pipe_behind == 1)
		close_write_and_open_read(all);
	if (all->data->pipe == 1 && all->data->pipe_behind == 1)
	{
		pipe(all->fildes2);

		all->save1 = dup(1);
		if (close(1) == -1)
			error_message("close 1");
		dup2(all->fildes2[1], 1);	//open write for new pipe
		if (close(all->fildes2[1]) == -1)
			error_message("close fildes2[1] 1");
	}
}

void	close_file_or_pipe_read(t_all *all)
{
	if (all->data->pipe_behind == 1)
	{
		dup2(all->save0, 0);
		if (close(all->save0) == -1)
			error_message("close save0");	//close read
	}
	if (all->data->pipe == 1 && all->data->pipe_behind == 1)
	{
		all->fildes1[0] = all->fildes2[0];
		all->fildes1[1] = all->fildes2[1];
	}
	if (all->data->red_to == 1 || all->data->doub_red_to == 1)
	{
		dup2(all->save1_red, 1);
		if (close(all->save1_red) == -1)
			error_message("close save1 while red_to");
	}
	else if (all->data->red_from == 1)
	{
		dup2(all->save0_red, 0);
		if (close(all->save0_red) == -1)
			error_message("close save0 while red_from");
	}
}
