/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:27:00 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/19 20:23:18 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include "./libft/libft.h"


typedef	struct s_all
{
	char	**env_vars;
	size_t	env_amount;
	int		child_killed;
}				t_all;

/*
**		builtins
*/
int		ft_cd(char *path, t_all *all);
int		ft_pwd(void);
void	ft_env(t_all *all);
void	ft_unset(t_all *all, char **args);
void	ft_export(t_all *all, char **args);
/*
**		utils
*/
void	free_ptrs_array(char **ptr_array);
void	exec_cmds(t_all *all, char **argv);
void	stat_test(char **file_names);
int		get_env_line(char *to_find, t_all *all);
char	*find_file_in_path(char	*file_name, t_all *all);
void	ctrl_c_handler(int signum);

#endif
