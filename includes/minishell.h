
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include "libft.h"
# include "errors.h"

# define SHELL_NAME "minishell"
# define MAIN_PROMPT "> \033[1;35m$\033[0m "
# define SIGQUIT_TERM "Quit: 3"

typedef struct		s_params
{
	int				i;
	int				quotes[2];
	int				arr[2];
}					t_params;

typedef enum		e_type
{
	END,
	ARG,
	REDIR,
	PIPE,
	PIPE_BEHIND
}					t_type;

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
	int				whence_the_command;
	int				is_semicolon;
	int				args_counter;
	int				redirs_counter;
	int				empty_env_var;
	int				fildes1[2];
	int				fildes2[2];
	int				save0;
	int				save1;
	int				save0_red;
	int				save1_red;
	t_params		params;
	t_data			*data;
}					t_all;

/*
**					builtins
*/
int					ft_cd(char *path, t_all *all);
int					ft_pwd(void);
int					ft_env(t_all *all);
int					ft_unset(t_all *all, char **args);
int					ft_export(t_all *all, char **args);
int					ft_echo(char **args);
int					ft_exit(char **args, t_all *all);

/*
**					utils
*/
void				print_export_without_args(t_all *all, int *mass);
void				free_ptrs_array(char **ptr_array);
int					exec_cmds(t_all *all, char **argv);
int					get_env_line_nbr(char *to_find, t_all *all);
void				envp_saving(char **envp, t_all *all);
char				*get_env_str(char *key, t_all *all);
int					edit_or_add_env_line(char *key, char *value, t_all *all);
void				env_init(t_all *all);
void				execution(t_all *all);

/*
**					errors handling
*/
int					print_error(char *command, char *argument,
					char *error_message);
void				print_error_with_arg(char *command, char *argument,
					char *error_message);
void				print_error_and_exit(char *command, char *argument,
					char *error_message, int exit_status);

/*
**					redirections & pipes
*/
void				output_to_file(t_all *all, char *file_name);
int					input_from_file(t_all *all, char *file_name);
void				open_pipe_write_and_close_read(t_all *all);
int					what_redirection(char *sign);

/*
**					parser
*/
void				parser(char *str, t_all *all);
int					is_terminating_pipe_in_line(char *line);
char				*get_line(void);
void				close_file(t_all *all, int is_error_while_open);
void				close_pipe_read(t_all *all);
int					split_args_and_redirects(char **array, t_all *all,
					int array_length);
void				counting_quotes(char *str, int *one_quotes, int *two_quotes,
					int i);
char				*get_env_str(char *key, t_all *all);
void				search_variable(t_all *all, char **word, char *str,
					int **arr);
int					filling_struct(t_all *all, t_list *new, int len);
int					line_search(char *line, t_all *all, int start, int end);
void				dash(t_all *all, char **word, char *str, int **start);
void				one_quotes(t_all *all, char **word, char *str, int **start);
void				two_quotes(t_all *all, char **word, char *str, int **start);
void				initial_params(t_all *all, int **start);
int					first_check_syntax_error(char *line, t_all *all);
int					syntax_check(t_all *all, char *str, int **arr,
					t_list **new);
void				help_arguments(t_all *all, char **str, int **arr,
					t_list **new);

/*
**					lists
*/
t_data				*p_lstnew(void);
void				p_lstadd_back(t_data **lst, t_data *new);
void				p_lstclear(t_data **lst);
t_data				*p_lstlast(t_data *lst);
int					p_lstsize(t_data *lst);

#endif
