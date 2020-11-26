#include "libft.h"
#include "minishell.h"

#ifdef ANTON
void			check_flags(char *str, t_data **temp, int i)
{
	if (str[i] == '|')
		(*temp)->pipe = 1;
	else if (str[i] == '<')
		(*temp)->red_from = 1;
	else if (str[i] == '>' && str[i + 1] != '>')
		(*temp)->red_to = 1;
	else if (str[i] == '>' && str[i + 1] == '>')
		(*temp)->doub_red_to = 1;
	// (*temp)->next = p_lstnew();
	// *temp = (*temp)->next;
}


void				parser(char *str, t_all *all)
{
	int			i;
	int			start;
	int			one_quotes;
	int			two_quotes;
	t_data		*temp;

	i = -1;
	start = 0;
	one_quotes = 0;
	two_quotes = 0;
	all->data = p_lstnew();
	temp = all->data;  // coхранили голову
	while (str[++i]) //поиск разделителя
	{
		if (str[i] == '\'')
			one_quotes++;
		else if (str[i] == '\"')
			two_quotes++;
		else if ((str[i] == ';' || str[i] == '|' || str[i] == '<' || str[i] == '>') &&
				(one_quotes % 2 == 0 && two_quotes % 2 == 0))
		{
			check_flags(str, &temp, i); // установка флагов под разделители
			line_search(str, &temp, start, i - 1); // обработка одной линии (строки) до разделителя
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			start = i + 1;
			temp->next = p_lstnew();
			if (temp->pipe)		//new
				temp->next->pipe_behind = 1;		//new
			temp = temp->next;
		}
	}
	line_search(str, &temp, start, i - 1); // когда дошли до конца строки, либо если разделителя не было
}

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
			error_message("GNL error");
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
				parser(all);
#endif
			all->head = all->data;
			// all->data = all->head;
			if (execution(all) == 0)
				break ;
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
	signal(SIGQUIT, ctrl_c_handler);
	// signal('\t', SIG_IGN);
	if (argc != 1 || !argv)
	{
		ft_putendl_fd("No parameters needed", 2);
		return (-1);
	}
	envp_saving(envp, &all);
	start_loop(&all);
	return (0);
}

