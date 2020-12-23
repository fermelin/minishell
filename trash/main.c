/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:26:13 by fermelin          #+#    #+#             */
/*   Updated: 2020/12/23 10:28:49 by fermelin         ###   ########.fr       */
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




// void	get_more_args(t_all *all)
// {
// 	char	*line;

// 	while (get_next_line(0, &line) != -1)
// 	{
// 		ft_putendl_fd("pipe> ", 1);

// 	}

// }


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
	ft_putstr_fd(MAIN_PROMPT, 1);
	parser(&all);
	return (0);
}
