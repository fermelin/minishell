/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:39:33 by gevelynn          #+#    #+#             */
/*   Updated: 2021/01/11 21:56:00 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	just_one_arg_processing(t_all *all, char *argv)
{
	if (argv && first_check_syntax_error(argv, all) != -1)
	{
		if (is_terminating_pipe_in_line(argv) != 1)
		{
			parser(argv, all);
			all->whence_the_command = 1;
			execution(all);
		}
		else
			all->exit_status = 2;
	}
}

static	void	main_loop(t_all *all)
{
	char	*line;

	line = NULL;
	ft_putstr_fd(MAIN_PROMPT, 2);
	while (1)
	{
		if ((line = get_line()) == NULL)
		{
			ft_putendl_fd("exit", 2);
			exit(all->exit_status);
		}
		if (line && (*line) && first_check_syntax_error(line, all) != -1)
		{
			parser(line, all);
			execution(all);
		}
		if (all->child_killed != 1 || all->exit_status == 131)
			ft_putstr_fd(MAIN_PROMPT, 2);
		all->child_killed = 0;
		free(line);
		line = NULL;
	}
}

static	void	struct_init(t_all *all)
{
	all->exit_status = 0;
	all->whence_the_command = 0;
	all->child_killed = 0;
	all->is_semicolon = 0;
}

int				main(int argc, char **argv, char **envp)
{
	t_all		all;

	struct_init(&all);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	envp_saving(envp, &all);
	env_init(&all);
	if (argc > 1 && argv[1] && ft_strncmp("-c", argv[1], 3) == 0)
		just_one_arg_processing(&all, argv[2]);
	else
		main_loop(&all);
	exit(all.exit_status);
}
