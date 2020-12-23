/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:35:07 by fermelin          #+#    #+#             */
/*   Updated: 2020/12/23 18:28:57 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	output_to_file(t_all *all, char *file_name)
{
	int	fd;

	fd = 0;
	if (all->data->redir == 1)
	{
		if ((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return ;
	}
	else if (all->data->redir == 2)
	{
		if ((fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
			return ;
	}
	all->save1_red = dup(1);
	dup2(fd, 1);
	if (close(fd) == -1)
		print_error("close", "fd", strerror(errno));
}

void	input_from_file(t_all *all, char *file_name)
{
	int	fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		print_error("open", file_name, strerror(errno));
		return ;
	}
	all->save0_red = dup(0);
	dup2(fd, 0);
	if (close(fd) == -1)
		print_error("close", "fd while input_from_file", strerror(errno));
}
