/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:42:29 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/24 10:24:34 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	prefix_trim(char const *s1, char const *set)
{
	size_t i;
	size_t j;
	size_t amount;

	i = 0;
	j = 0;
	amount = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				amount++;
				break ;
			}
			else
				j++;
		}
		if (amount == i)
			break ;
		i++;
	}
	return (amount);
}

static	size_t	suffix_trim(char const *s1, char const *set, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	amount;

	i = --len;
	j = 0;
	amount = 0;
	while (i)
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				amount++;
				break ;
			}
			else
				j++;
		}
		if (len - amount == i)
			break ;
		i--;
	}
	return (amount);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	size_t	pref;
	size_t	suf;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	if (s1)
	{
		while (s1[len])
			len++;
		pref = prefix_trim(s1, set);
		suf = suffix_trim(s1, set, len);
		len = len < pref + suf ? 0 : len - pref - suf;
		if (!(newstr = (char*)malloc((len + 1) * sizeof(char))))
			return (NULL);
		while (i < (len))
			newstr[i++] = s1[pref++];
		newstr[i] = '\0';
		return (newstr);
	}
	return (NULL);
}
