/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:32:51 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/24 15:45:19 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest1;
	unsigned char	*src1;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dest1 = (unsigned char*)dest;
	src1 = (unsigned char*)src;
	if (dest1 < src1)
		while (i < n)
		{
			dest1[i] = src1[i];
			i++;
		}
	else
	{
		i = 1;
		while (i <= n)
		{
			dest1[n - i] = src1[n - i];
			i++;
		}
	}
	return (dest);
}
