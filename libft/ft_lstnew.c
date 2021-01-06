/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:29:06 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/24 08:10:58 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
