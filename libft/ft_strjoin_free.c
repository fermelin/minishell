/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 20:19:32 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/04 20:20:16 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*newstr;
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(newstr = (char*)malloc((i + j + 1) * sizeof(char))))
		return (NULL);
	ptr = newstr;
	while (*s1)
		*newstr++ = *s1++;
	free(s1 - i);
	s1 = NULL;
	while (*s2)
		*newstr++ = *s2++;
	*newstr = '\0';
	return (ptr);
}
