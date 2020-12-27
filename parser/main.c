#include "libft.h"
#include "minishell.h"

int			counting_quotes(char *str, int one_quotes, int two_quotes, int i)
{
	if(str[i] == '\'')
	{   
		one_quotes++;
		if(two_quotes % 2 || (str[i - 1] == '\\' && one_quotes % 2))
			one_quotes++;
		return (one_quotes);
	}
	else if(str[i] == '\"')
	{
		two_quotes++;
		if(one_quotes % 2 || (str[i - 1] == '\\'))
			two_quotes++;
		return (two_quotes);
	}
	return (0);
}

void	temporary_loop(t_all *all)
{
	if (execution(all) == 0)
		exit (0);

}

void				parser(char *str, t_all *all)
{
	int			i;
	int			start;
	int			one_quotes;
	int			two_quotes;

	i = -1;
	start = 0;
	one_quotes = 0;
	two_quotes = 0;
	all->head = p_lstnew();
	all->data = all->head;
	all->tmp = all->data;
	while (str[++i]) //поиск разделителя
	{
		if(str[i] == '\'')
			one_quotes = counting_quotes(str, one_quotes, two_quotes, i);
		else if(str[i] == '\"')
			two_quotes = counting_quotes(str, one_quotes, two_quotes, i);
		else if ((str[i] == ';' && (i != 0 && str[i - 1] != '\\')) && //|| str[i] == '|')  && //|| str[i] == '<' || str[i] == '>')	!!!!!!!!!Добавил экранирование точки с запятой !!!!!!!!!!
				(one_quotes % 2 == 0 && two_quotes % 2 == 0))
		{
			// if (str[i] == '|')
			// 	all->data->pipe = 1; // установка флагов под разделители
			all->tmp = all->data;
			line_search(str, all, start, i - 1); // обработка одной линии (строки) до разделителя
			all->data = all->tmp;
			if (execution(all) == 0)
				exit (0);
			all->data = all->tmp;
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			start = i + 1;
			p_lstclear(&(all->head));
			all->head = p_lstnew();
			all->data = all->head;
			// // if (all->data->pipe)
			// // 	all->data->next->pipe_behind = 1;
			// all->data = all->data->next;
		}
	}
	line_search(str, all, start, i - 1); // когда дошли до конца строки, либо если разделителя не было
	all->data = all->tmp;
}

char			*get_line(void)
{
	static char *line2;
	char		*line;
	int			ret;

	line2 = NULL;
	while ((ret = get_next_line(0, &line)) != 1)
	{
		if (ret == -1)
		{
			print_error("GNL", "", "error");
			return (NULL);
		}
		if ((!line || !(*line)) && (!line2 || !(*line2)))
			return (NULL);
		else if (*line)
		{
			line2 = ft_strjoin(line2, line);
			line = NULL;
		}
	}
	if (line2 && (*line2))
		line = ft_strjoin(line2, line);
	return (line);
}

void	start_checker(t_all *all, char *argv)
{
	if (argv)
		parser(argv, all);
	if (execution(all) == 0)
		;
	p_lstclear(&(all->head));
}

void			start_loop(t_all *all)
{
	char 		*line;

	line = NULL;
	ft_putstr_fd(MAIN_PROMPT, 2);
	while (1)
	{
		if ((line = get_line()) == NULL)
			exit(0);						//print exit before it

		if (line && (*line))
		{
			parser(line, all);
		}
		if (execution(all) == 0)				//uncomment
			exit(0);								//uncomment
		if (all->child_killed != 1)
			ft_putstr_fd(MAIN_PROMPT, 2);
		all->child_killed = 0;
		free (line);
		line = NULL;
		p_lstclear(&(all->head));
	}
	free(line);
	ft_putendl_fd("exit", 1);
}

void			pwd_init(t_all *all)		//to delete to delete to delete to delete to delete 
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	edit_or_add_env_line("PWD=", cwd, all);
	edit_or_add_env_line("SHLVL=", "1", all);
	// edit_or_add_env_line("TERM=", "xterm-256color", all);
	free(cwd);
}

int				main(int argc, char **argv, char **envp)
{	
	t_all		all;

	all.exit_status = 0;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_c_handler);
	if (!argc || !argv)
	{
		ft_putendl_fd("No parameters needed", 2);
		return (-1);
	}
	envp_saving(envp, &all);
	pwd_init(&all);
	if (argv[1] && ft_strncmp("-c", argv[1], 3) == 0)
		start_checker(&all, argv[2]);
	else
		start_loop(&all);
	return (all.exit_status);
}
