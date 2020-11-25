#include "../libft/libft.h"
#include "../minishell.h"

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
	else
		;
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
			temp = temp->next;
		}
	}
	line_search(str, &temp, start, i - 1); // когда дошли до конца строки, либо если разделителя не было
}

void			start_loop(t_all *all)
{
	char 		*line;

	ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
	while (get_next_line(0, &line) > 0)
	{
		parser(line, all);
		all->head = all->data;
		if (execution(all) == 0)
			break ;	
		if (all->child_killed != 1)
			ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
		all->child_killed = 0;
		free (line);
		line = NULL;
		p_lstclear(&(all->head));
		// if (all->child_killed != 1)
			// ft_putstr_fd("> \033[1;35m$\033[0m ", 1);
		all->child_killed = 0;
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
	if (argc != 1 || !argv)
	{
		ft_putendl_fd("No parameters needed", 2);
		return (-1);
	}
	envp_saving(envp, &all);
	start_loop(&all);
	return (0);
}

