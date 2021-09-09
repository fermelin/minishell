
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newelem;

	if (!(newelem = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	newelem->content = content;
	newelem->next = NULL;
	return (newelem);
}
