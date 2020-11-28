#include "libft.h"
#include "minishell.h"

#ifdef ANTON
// void			check_flags(char *str, t_data *temp, int i)
// {
// 	if (str[i] == '|')
// 		temp->pipe = 1;
// 	else if (str[i] == '<')
// 		temp->red_from = 1;
// 	else if (str[i] == '>' && str[i + 1] != '>')
// 		temp->red_to = 1;
// 	else if (str[i] == '>' && str[i + 1] == '>')
// 		temp->doub_red_to = 1;
// }

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
	all->data = p_lstnew();
	all->head = all->data;
	while (str[++i]) //поиск разделителя
	{
		if(str[i] == '\'')
			one_quotes = counting_quotes(str, one_quotes, two_quotes, i);
		else if(str[i] == '\"')
			two_quotes = counting_quotes(str, one_quotes, two_quotes, i);
		else if ((str[i] == ';' || str[i] == '|')  && //|| str[i] == '<' || str[i] == '>')
				(one_quotes % 2 == 0 && two_quotes % 2 == 0))
		{
			if (str[i] == '|')
				all->data->pipe = 1; // установка флагов под разделители
			line_search(str, all, start, i - 1); // обработка одной линии (строки) до разделителя
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			start = i + 1;
			all->data->next = p_lstnew();
			if (all->data->pipe)
				all->data->next->pipe_behind = 1;
			all->data = all->data->next;
		}
	}
	line_search(str, all, start, i - 1); // когда дошли до конца строки, либо если разделителя не было
}

// void				parser(char *str, t_all *all)
// {
// 	int			i;
// 	int			start;
// 	int			one_quotes;
// 	int			two_quotes;
// 	// t_data		*temp;

// 	i = -1;
// 	start = 0;
// 	one_quotes = 0;
// 	two_quotes = 0;
// 	all->data = p_lstnew();
// 	all->head = all->data;
// 	// temp = all->data;  // coхранили голову
// 	while (str[++i]) //поиск разделителя
// 	{
//         if (str[i] == '\"')
//             two_quotes++;
//         if (str[i] == '\"' && str[i - 1] == '\\')
//             two_quotes--;
//         else if (str[i] == '\'')
//             one_quotes++;
// 		else if ((str[i] == ';' || str[i] == '|' || str[i] == '<' || str[i] == '>') &&
// 				(one_quotes % 2 == 0 && two_quotes % 2 == 0))
// 		{
// 			check_flags(str, all->data, i); // установка флагов под разделители
// 			line_search(str, all, start, i - 1); // обработка одной линии (строки) до разделителя
// 			if (str[i] == '>' && str[i + 1] == '>')
// 				i++;
// 			start = i + 1;
// 			all->data->next = p_lstnew();
// 			if (all->data->pipe)
// 				all->data->next->pipe_behind = 1;
// 			// execution(all);								//added by myself
// 			all->data = all->data->next;
// 		}
// 	}
// 	line_search(str, all, start, i - 1); // когда дошли до конца строки, либо если разделителя не было
// }

#endif

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
#ifdef ANTON
				parser(argv, all);
#endif
#ifndef ANTON
				my_parser(argv, all);
#endif
	all->data = all->head;
	if (execution(all) == 0)
		;
	p_lstclear(&(all->head));
}

void			start_loop(t_all *all)
{
	char 		*line;
	// int			ret;

	line = NULL;
	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	while (1)
	{
			if ((line = get_line()) == NULL)
				break ;
			if (line && (*line))
#ifdef ANTON
				parser(line, all);
#endif
#ifndef ANTON
				my_parser(line, all);
#endif
			all->head = all->data;
			if (execution(all) == 0)				//uncomment
				break ;								//uncomment
			if (all->child_killed != 1)
				ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
			all->child_killed = 0;
			free (line);
			line = NULL;
			p_lstclear(&(all->head));

	}
	free(line);
	ft_putendl_fd("exit", 1);
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
	if (argv[1] && ft_strncmp("-c", argv[1], 3) == 0)
		start_checker(&all, argv[2]);
	else
		start_loop(&all);
	return (all.exit_status);
}
