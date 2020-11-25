/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:27:00 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/25 17:37:13 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "./libft/libft.h"

typedef struct		s_data
{
	char			**args;
	char			*file_name;
	int				pipe;
	int				pipe_behind;
	int				red_to;
	int				doub_red_to;
	int				red_from;
	struct s_data	*next;
}					t_data;

typedef	struct		s_all
{
	char			**env_vars;
	size_t			env_amount;
	int				child_killed;
	int				exit_status;
	int				fildes1[2];
	int				fildes2[2];
	int				save0;
	int				save1;	//pipes and redirections may conflict about it

	t_data			*data;
	t_data			*head;
}					t_all;



/*
**		builtins
*/
int		ft_cd(char *path, t_all *all);
int		ft_pwd(void);
int		ft_env(t_all *all);
int		ft_unset(t_all *all, char **args);
int		ft_export(t_all *all, char **args);
/*
**		utils
*/
void	free_ptrs_array(char **ptr_array);
int		exec_cmds(t_all *all, char **argv);
int		stat_test(char **file_names);
int		get_env_line_nbr(char *to_find, t_all *all);
char	*find_file_in_path(char	*file_name, t_all *all);
void	ctrl_c_handler(int signum);
void	error_message(char *text_error);
void	envp_saving(char **envp, t_all *all);
/*
**		to delete to delete to delete to delete 
*/
t_data	*p_lstnew(void);
void	p_lstadd_back(t_data **lst, t_data *new);
void	p_lstadd_front(t_data **lst, t_data *new);
void	p_lstclear(t_data **lst);
void	p_lstdelone(t_data *lst);
t_data	*p_lstlast(t_data *lst);
int		p_lstsize(t_data *lst);

/*
**		to delete to delete to delete to delete 
*/
void	parser_to_list(t_all *all, char **splited);
void	parser(t_all *all);
int		execution(t_all *all);
/*
**		redirections & pipes
*/
void	output_to_file(t_all *all);
void	input_from_file(t_all *all);
void	open_pipe_write_and_close_read(t_all *all);
void	close_file_or_pipe_read(t_all *all);

#endif
