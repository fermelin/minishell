#include "libft.h"
#include "minishell.h"


void	error_malloc()
{
		write(1, "Error malloc\n", 13);
		return ;
}

void	filling_struct_elem(int first_word, char **array, int *choice, t_all *all)
{
	int i;
	int j;
	int g;
	// int h;

	i = 0;
	j = 0;
	g = 0;
	i = first_word;
	while (choice[i] != END)
	{
		if (choice[i] == ARG)
			all->data->args[j++] = array[i];
		else if (choice[i] == REDIR)
		{
			all->data->redir_array[g++] = array[i++];
			all->data->redir_array[g++] = array[i];
		}
		else if (choice[i] == PIPE)
		{
			all->data->pipe = 1;
			all->data->next = p_lstnew();
			all->data->next->pipe_behind = 1;
			all->data = all->data->next;
			break;
		}
		i++;
	}
}

void	allocate_memory_for_struct(t_all *all, int args_count, int redirs_count)
{
	if (args_count != 0 && all->data && !(all->data->args = ft_calloc(args_count + 1, sizeof(char*))))
		return ;
	if (redirs_count != 0 && all->data)
	{
		if (!(all->data->redir_array = ft_calloc(redirs_count + 1, sizeof(char*))))
			return ;
		all->data->redir = 1;
	}
}

int	*split_args_and_redirects(char **array, t_all *all)
{
	int j;
	int	redirs_count;
	int	args_count;
	int	*choice;
	int	first_word;
	enum	e_type;

	j = 0;
	first_word = 0;
	redirs_count = 0;
	args_count = 0;
	while (array[j])
		j++;
	if (!(choice = ft_calloc(j + 1, sizeof(int))))
		return (0);									//error handling
	j = 0;
	 while (array[j])
	{
		while (array[j] && what_redirection(array[j]) == 0 && ft_strncmp("|", array[j], 2) != 0)
		{
			choice[j] = ARG;
			args_count++;
			j++;
		}
		while (array[j] && array[j + 1] && what_redirection(array[j]) != 0)
		{
			choice[j] = REDIR;
			j += 2;
			redirs_count += 2;
		}
		if (array[j] && ft_strncmp("|", array[j], 2) == 0)
		{
			allocate_memory_for_struct(all, args_count, redirs_count);
			choice[j] = PIPE;
			filling_struct_elem(first_word, array, choice, all);
			j++;
			first_word = j;
			redirs_count = 0;
			args_count = 0;
		}
	}
	allocate_memory_for_struct(all, args_count, redirs_count);
	filling_struct_elem(first_word, array, choice, all);
	return (choice);
}

void filling_struct(t_all *all, t_list *new, int len)
{
	t_list *new_copy;
	char **array;
	int		*choice;
	int		i;
	int		j;
	int		g;
	int 	h;

	i = 0;
	j = 0;
	g = 0;
	h = 0;
	new_copy = new;
	// while (temp->next)
	// 	temp = temp->next;

	array = ft_calloc(len + 1, sizeof(char *));		//temp->args = (char **)malloc(sizeof(char*) * (len + 1)) 
	while(new_copy)
	{
		array[i] = new_copy->content;
		new_copy = new_copy->next;
		i++;
	}
	choice = split_args_and_redirects(array, all);
	// elem = temp;
	// {
		
	// }
	free(choice);
	free(array);
}





// int add_string(t_data **elem, char **str, int len)
// {
// 	int i;
// 	char **temp;

// 	i = -1;
// 	if (!(temp = (char **)malloc(sizeof(char *) * len)))
// 		return (0);
// 	while (++i < len)
// 	{
// 		if (!(temp[i] = (char *)malloc(sizeof(char) * ft_strlen((*elem)->args[i]))))
// 			return (0);
// 		temp[i] = (*elem)->args[i];
// 	}

// }

// int malloc_array(t_data **elem, char **str)
// {
// 	int i;
// 	int len;

// 	i = 0;
// 	len = 0;
// 	if (!((*elem)->args))
// 	{
// 		if (!((*elem)->args = (char **)malloc(sizeof(char *) * 2)) || // защитить
// 			!((*elem)->args[0] = (char *)malloc(sizeof(char) * ft_strlen(*str))))
// 			return (0);
// 		(*elem)->args[0] = *str;
// 		(*elem)->args[1] = NULL;
// 	}
// 	else
// 	{
// 		while ((*elem)->args[len])
// 			len++;
// 		if (!(add_string(elem, str, len)))
// 			return (0);
// 	}
// 	return (1);
// }