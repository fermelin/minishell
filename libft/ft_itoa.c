/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 20:06:33 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/24 16:38:14 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		digit_counter(int n)
{
	int count;

	count = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n >= 1)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	char	*nbr;
	int		count;

	count = digit_counter(n);
	if (!(nbr = (char*)malloc((count + 1) * sizeof(char))))
		return (NULL);
	nbr[count--] = '\0';
	if (n == 0)
		nbr[count] = '0';
	if (n < 0)
	{
		nbr[0] = '-';
		if (n == -2147483648)
		{
			nbr[1] = '2';
			n = -147483648;
		}
		n = -n;
	}
	while (n >= 1)
	{
		nbr[count--] = n % 10 + '0';
		n /= 10;
	}
	return (nbr);
}
