/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:35:07 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/25 16:52:11 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	output_to_file(t_all *all)
{
	int	fd;

	fd = 0;
	if (all->data->red_to == 1)
	{
		if ((fd = open(all->data->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return ;
	}
	else if (all->data->doub_red_to == 1)
	{
		if ((fd = open(all->data->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
			return ;
	}
	all->save1 = dup(1);

	dup2(fd, 1);
	if (close(fd) == -1)
		error_message("close fd");

}

void	input_from_file(t_all *all)
{
	int	fd;

	if ((fd = open(all->data->file_name, O_RDONLY)) == -1)
	{
		error_message("open");
		return ;
	}
	all->save0 = dup(0);
	dup2(fd, 0);
	if (close(fd) == -1)
		error_message("close fd while input_from_file");
}
