/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 16:44:31 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/24 14:00:25 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*dest1;
	unsigned char	c1;

	i = 0;
	src1 = (unsigned char*)src;
	dest1 = (unsigned char*)dest;
	c1 = (unsigned char)c;
	if (dest || src)
	{
		while (i < n)
		{
			dest1[i] = src1[i];
			if (src1[i] == c1)
				return (dest + i + 1);
			i++;
		}
	}
	return (NULL);
}
