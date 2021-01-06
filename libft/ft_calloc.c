/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:25:23 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/24 07:40:22 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	amount;
	char	*str;

	amount = nmemb * size;
	if (!(str = (char*)malloc(amount * sizeof(char))))
		return (NULL);
	ft_bzero(str, amount);
	return (str);
}
