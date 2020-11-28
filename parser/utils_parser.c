#include "libft.h"
#include "minishell.h"


void	error_malloc()
{
		write(1, "Error malloc\n", 13);
		return ;
}

int	*split_args_and_redirects(char **array, t_data *elem)
{

	// t_list	*args;
	// t_list	*redirs;
	// t_list	*args_head;
	// t_list	*redirs_head;
	// i = 0;
	// j = 0;

	// args = ft_lstnew(NULL);
	// redirs = ft_lstnew(NULL);
	// args_head = args;
	// redirs_head = redirs;
	// while (new)
	// {
	// 	while (new && what_redirection(new->content) == 0)
	// 	{
	// 		args->next = ft_lstnew(new->content);
	// 		args = args->next;
	// 		i++;
	// 	}
	// 	while (what_redirection(new->content) != 0 && new->next)
	// 	{
	// 		j += 2;
	// 	}

	// }

	// int	i;
	int j;
	int	redirs_count;
	int	args_count;
	int	*choice;

	j = 0;
	// i = 0;
	redirs_count = 0;
	args_count = 0;
	while (array[j])
		j++;
	if (!(choice = ft_calloc(j + 1, sizeof(int))))
		return (0);									//error handling
	j = 0;
	 while (array[j])
	{
		while (array[j] && what_redirection(array[j]) == 0)
		{
			choice[j] = 1;
			args_count++;
			j++;
		}
		while (array[j] && array[j + 1] && what_redirection(array[j]) != 0)
		{
			j += 2;
			redirs_count += 2;
		}
	}
	if (!(elem->args = ft_calloc(args_count + 1, sizeof(char*))))
		return (0);
	if (!(elem->redir_array = ft_calloc(redirs_count + 1, sizeof(char*))))
		return (0);
	if (redirs_count != 0)
		elem->redir = 1;
	return (choice);
	
	


}

void filling_struct(t_data **elem, t_list *new, int len)
{
	// int		args_count;
	// int		redir_array_count;
	t_data	*temp;
	// t_list	*head;
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

	temp = *elem;
	while (temp->next)
		temp = temp->next;

	array = ft_calloc(len + 1, sizeof(char *));		//temp->args = (char **)malloc(sizeof(char*) * (len + 1)) 
	while(new)
	{
		array[i] = new->content;
		new = new->next;
		i++;
	}
	choice = split_args_and_redirects(array, temp);
	while (h < i)
	{
		if (choice[h] == 1)
			temp->args[j++] = array[h];
		else
			temp->redir_array[g++] = array[h];
		h++;
	}
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