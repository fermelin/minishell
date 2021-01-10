/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:39:33 by gevelynn          #+#    #+#             */
/*   Updated: 2021/01/11 00:59:58 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			counting_quotes(char *str, int *one_quotes, int *two_quotes, int i)
{
	if(str[i] == '\'')
	{   
		(*one_quotes)++;
		if((*two_quotes) % 2 || (str[i - 1] == '\\' && (*one_quotes) % 2))
			(*one_quotes)++;
	}
	else if(str[i] == '\"')
	{
		(*two_quotes)++;
		if((*one_quotes) % 2 || (str[i - 1] == '\\'))
			(*two_quotes)++;
	}
}



void			parser(char *str, t_all *all)
{
	int			i;
	int			start;
	int			one_quotes;
	int			two_quotes;

	i = -1;
	start = 0;
	one_quotes = 0;
	two_quotes = 0;
	while (str[++i]) //поиск разделителя
	{
		if(str[i] == '\'' || str[i] == '\"')
			counting_quotes(str, &one_quotes, &two_quotes, i);
		else if ((str[i] == ';' && (i != 0 && str[i - 1] != '\\')) && //|| str[i] == '|')  && //|| str[i] == '<' || str[i] == '>')	!!!!!!!!!Добавил экранирование точки с запятой !!!!!!!!!!
				(one_quotes % 2 == 0 && two_quotes % 2 == 0))
		{
			if (line_search(str, all, start, i - 1) == -1) // обработка одной линии (строки) до разделителя
				return ;
			execution(all);
			start = i + 1;
		}
	}
	line_search(str, all, start, i - 1); // когда дошли до конца строки, либо если разделителя не было
}

int				is_terminating_pipe_in_line(char *line)
{
	int i;

	i = 0;
	if (line)
	{
		i = ft_strlen(line) - 1;
		while (i >= 0 && (line[i] == ' ' || line[i] == '\t'))
			i--;
		if (i > 0 && line[i] == '|')
		{
			ft_putstr_fd("pipe> ", 2);
			return (1);
		}
	}
	return (0);
}

char			*get_line(void)
{
	char	*line2;
	char	*line;
	int		ret;

	line = NULL;
	line2 = NULL;
	while ((ret = get_next_line(0, &line)) != 1 || is_terminating_pipe_in_line(line) == 1)
	{
		if (ret == -1)
		{
			print_error("GNL", "", "error");
			return (NULL);
		}
		if ((!line || !(*line)) && (!line2 || !(*line2)))
		{
			free(line);
			return (NULL);
		}
		ft_putstr_fd("  \b\b", 1);
		if (*line)
			line2 = ft_strjoin_free(line2, line);
		free(line);
	}
	line2 = ft_strjoin_free(line2, line);
	free(line);
	return (line2);
}

void			start_checker(t_all *all, char *argv)
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

void			main_loop(t_all *all)
{
	char 		*line;

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
		if (all->child_killed != 1)
			ft_putstr_fd(MAIN_PROMPT, 2);
		all->child_killed = 0;
		free (line);
		line = NULL;
	}
}

void			env_init(t_all *all)		//to delete to delete to delete to delete to delete 
{
	char	*cwd;
	char	*shlvl_str;
	int		shlvl_int;

	cwd = getcwd(NULL, 0);
	edit_or_add_env_line("PWD=", cwd, all);
	if (!(shlvl_str = get_env_str("SHLVL", all)))
		edit_or_add_env_line("SHLVL=", "1", all);
	else
	{
		shlvl_int = ft_atoi(shlvl_str) + 1;
		free(shlvl_str);
		shlvl_str = ft_itoa(shlvl_int);
		edit_or_add_env_line("SHLVL=", shlvl_str, all);
		free(shlvl_str);
	}
	free(cwd);
}

void			struct_init(t_all *all)
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
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_backslash_handler);
	envp_saving(envp, &all);
	env_init(&all);
	if (argc > 1 && argv[1] && ft_strncmp("-c", argv[1], 3) == 0)
		start_checker(&all, argv[2]);
	else
		main_loop(&all);
	exit (all.exit_status);
}
