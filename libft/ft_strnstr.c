/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 17:11:30 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/19 00:03:31 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!little[j])
		return ((char*)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
		{
			j++;
			if (little[j] == '\0' || (!big[i] && !little[j]))
				return (&((char*)big)[i + 1 - j]);
		}
		else
		{
			i -= j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}
