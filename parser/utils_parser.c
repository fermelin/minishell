#include "libft.h"
#include "minishell.h"


void	error_malloc()
{
		write(1, "Error malloc\n", 13);
		return ;
}

void filling_struct(t_data **elem, t_list *new, int len)
{
	int		i;
	t_data	*temp;

	i = 0;
	temp = *elem;
	while (temp->next)
		temp = temp->next;
	temp->args = ft_calloc(len + 1, sizeof(char *));		//temp->args = (char **)malloc(sizeof(char*) * (len + 1)) 
	while(new)
	{
		temp->args[i] = new->content;
		new = new->next;
		i++;
	}
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