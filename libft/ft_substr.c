/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 12:28:01 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/25 21:52:14 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		;
	else
		while (s[start + i] && i < len)
			i++;
	if (!(newstr = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	while (j < i)
	{
		newstr[j] = s[start + j];
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}
