/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 16:46:51 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/24 08:09:31 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;

	if (!lst)
		return ;
	while ((*lst))
	{
		tmp = (*lst)->next;
		if (del)
			(*del)((*lst)->content);
		(*lst) = tmp;
		free(*lst);
	}
	lst = NULL;
}
