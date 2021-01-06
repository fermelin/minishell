/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 12:10:09 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/24 10:41:43 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*newstr;

	if (!(newstr = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	ft_strlcpy(newstr, s, ft_strlen(s) + 1);
	return (newstr);
}
