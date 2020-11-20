/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:35:07 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/20 19:14:07 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	output_to_file(t_all *all, char **argv)		// cat > file.txt
{
	int	fd;
	int	save1;

	if ((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		return ;
	save1 = dup(1);
	dup2(fd, 1);
	close(fd);
	child_process(all, argv);
	dup2(save1, 1);
	close(save1);
}

void	input_from_file(char *command, char *file_name)		// grep search-word < filename
{
	
}
