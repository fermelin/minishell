/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 11:53:28 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/22 12:56:18 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	c2;

	i = 0;
	c2 = (unsigned char)c;
	while (i < n)
	{
		if (((unsigned char*)s)[i] == c2)
			return ((void*)s + i);
		i++;
	}
	return (NULL);
}
