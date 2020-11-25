#include "../minishell.h"

t_data	*p_lstlast(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int		p_lstsize(t_data *lst)
{
	size_t i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	p_lstdelone(t_data *lst, void (*del)(void*))
{
	if (lst)
	{
		if (del)
		{
			del(lst->file_name);
			if ((lst->args))
			{
				while ((*(lst->args)))
				{
					del(*(lst->args));
					lst->args++;
				}
				del(lst->args);
			}
		}
		free(lst);
		lst = NULL;
	}
}

void	p_lstclear(t_data **lst)
{
	t_data *tmp;

	if (!lst)
		return ;
	while ((*lst))
	{
		tmp = (*lst)->next;
		free_ptrs_array((*lst)->args);
		free((*lst)->file_name);
		free(*lst);
		(*lst) = tmp;
	}
	lst = NULL;
}

void	p_lstadd_back(t_data **lst, t_data *new)
{
	t_data *tmp;

	if (new && lst)
	{
		tmp = p_lstlast(*lst);
		if (!tmp)
			*lst = new;
		else
			tmp->next = new;
	}
}