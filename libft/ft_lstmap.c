
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*beginning;

	if (!lst || !f || !(newlst = ft_lstnew((*f)(lst->content))))
		return (NULL);
	beginning = newlst;
	while (lst->next)
	{
		lst = lst->next;
		if (lst && !(newlst->next = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&beginning, del);
			return (NULL);
		}
		newlst = newlst->next;
	}
	return (beginning);
}
