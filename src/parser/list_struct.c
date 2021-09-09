
#include "minishell.h"

t_data	*p_lstnew(void)
{
	t_data	*new_elem;

	if (!(new_elem = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	new_elem->args = NULL;
	new_elem->redir_array = NULL;
	new_elem->pipe = 0;
	new_elem->pipe_behind = 0;
	new_elem->redir = 0;
	new_elem->next = NULL;
	return (new_elem);
}

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

void	p_lstclear(t_data **lst)
{
	t_data *tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		free_ptrs_array(tmp->args);
		free_ptrs_array(tmp->redir_array);
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = NULL;
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
