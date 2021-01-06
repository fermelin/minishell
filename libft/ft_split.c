/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:21:32 by fermelin          #+#    #+#             */
/*   Updated: 2020/05/29 10:32:59 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	word_counter(char const *s, char c)
{
	size_t	i;
	size_t	amount;

	i = 0;
	amount = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			amount++;
		while (s[i] != c && s[i])
			i++;
	}
	return (amount);
}

static	void	*array_free(char **array, size_t j)
{
	while (j != 0)
		free(array[--j]);
	free(array);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;
	size_t	words;

	j = 0;
	words = (!s || !(*s)) ? 0 : (word_counter(s, c) + 1);
	if (words == 0 || !(array = (char**)malloc(words * sizeof(char*))))
		return (NULL);
	while (j + 1 < words)
	{
		i = 0;
		while (*s == c && *s)
			s++;
		while (*(s + i) != c && *(s + i))
			i++;
		if (!(array[j] = (char*)malloc((i + 1) * sizeof(char))))
			return (array_free(array, j));
		i = 0;
		while (*s != c && *s)
			array[j][i++] = *s++;
		array[j++][i] = '\0';
	}
	array[j] = NULL;
	return (array);
}
