/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:27:00 by fermelin          #+#    #+#             */
/*   Updated: 2020/12/22 15:37:54 by fermelin         ###   ########.fr       */
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
#include "libft.h"
#include "errors.h"

	typedef enum e_type
	{
		END,
		ARG,
		REDIR,
		PIPE,
		PIPE_BEHIND
	}	t_type;

	typedef enum e_redir
	{
		NO_RED,
		RED_TO,
		DOUB_RED_TO,
		RED_FROM
	}			t_redir;

typedef struct		s_data
{
	char			**args;
	char			**redir_array;
	int				pipe;
	int				pipe_behind;
	int				redir;
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
	int				save0_red;
	int				save1_red;
	t_type			type;
	t_data			*data;
	t_data			*tmp;
	t_data			*head;
}					t_all;








// to delete  to delete  to delete  to delete  to delete  to delete  to delete  to delete  to delete  to delete 
// typedef struct		s_data 
// {
// 	int				token_type[4];
// 	char			*args;
// 	int				pipe;
// 	int				pipe_behind;



// }					t_data;
// to delete  to delete  to delete  to delete  to delete  to delete  to delete  to delete  to delete  to delete 

/*
**		builtins
*/
int		ft_cd(char *path, t_all *all);
int		ft_pwd(void);
int		ft_env(t_all *all);
int		ft_unset(t_all *all, char **args);
int		ft_export(t_all *all, char **args);
int		ft_echo(char **args);
int		ft_exit(char **args);
/*
**		utils
*/
void	free_ptrs_array(char **ptr_array);
int		exec_cmds(t_all *all, char **argv);
int		stat_test(char **file_names);
int		get_env_line_nbr(char *to_find, t_all *all);
int		find_file_in_path(char	*file_name, char **path, t_all *all);
void	ctrl_c_handler(int signum);
void	error_message(char *text_error);
void	envp_saving(char **envp, t_all *all);
char	*get_env_str(char *key, t_all *all);
int		edit_or_add_env_line(char *key, char *value, t_all *all);
/*
**		errors handling
*/
void	print_error(char *command, char *argument, char *error_message);
void	print_unset_or_export_error(char *command, char *argument, char *error_message);
// /*
// **		to delete to delete to delete to delete 
// */
// t_data	*p_lstnew(void);
// void	p_lstadd_back(t_data **lst, t_data *new);
// void	p_lstadd_front(t_data **lst, t_data *new);
// void	p_lstclear(t_data **lst);
// void	p_lstdelone(t_data *lst);
// t_data	*p_lstlast(t_data *lst);
// int		p_lstsize(t_data *lst);

/*
**		to delete to delete to delete to delete 
*/
int		execution(t_all *all);
int		choose_command(t_all *all);
/*
**		redirections & pipes
*/
void	output_to_file(t_all *all, char *file_name);
void	input_from_file(t_all *all, char *file_name);
void	open_pipe_write_and_close_read(t_all *all);
void	close_file_or_pipe_read(t_all *all);
int		what_redirection(char *sign);
/*
**		parser
*/
// void 	filling_struct(t_all *all, t_list *new, int len);
// void	line_search(char *line, t_all *all, int start, int end);
// t_data	*p_lstnew(void);
// void	p_lstadd_back(t_data **lst, t_data *new);
// void	p_lstclear(t_data **lst);
// t_data	*p_lstlast(t_data *lst);
// int		p_lstsize(t_data *lst);
// void	p_lstdelone(t_data *lst, void (*del)(void*));
// void	error_malloc();
// int        check_dollar(t_all *all, char **word, int i);
// char		*search_variable(t_all *all, char **word);
// int delete_symbol(char **str, int i, char c);
// int			counting_quotes(char *str, int one_quotes, int two_quotes, int i);
void	close_file(t_all *all);
void	close_pipe_read(t_all *all);

int		counting_quotes(char *str, int one_quotes, int two_quotes, int i);
int		check_dollar(t_all *all, char **word, int start, int *arr);
char	*get_env_str(char *key, t_all *all);
int		delete_symbol(char **str, int i, char c);
void	search_variable(t_all *all, char **word, char *str, int *arr);
void 	filling_struct(t_all *all, t_list *new, int len);
void	line_search(char *line, t_all *all, int start, int end);
t_data	*p_lstnew(void);
void	p_lstadd_back(t_data **lst, t_data *new);
void	p_lstclear(t_data **lst);
t_data	*p_lstlast(t_data *lst);
int		p_lstsize(t_data *lst);
void	p_lstdelone(t_data *lst, void (*del)(void*));
void	error_malloc();

#endif
