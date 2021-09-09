
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		if (del)
			(*del)((*lst)->content);
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = NULL;
}
