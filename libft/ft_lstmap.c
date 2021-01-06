/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 20:12:06 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/24 08:10:15 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
