
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t g;

	i = 0;
	j = 0;
	g = 0;
	if (size != 0)
	{
		while (dst[i] && i < size)
			i++;
		while (i + 1 < size && src[j])
			dst[i++] = src[j++];
		if (j != 0)
			dst[i] = '\0';
	}
	while (src[j + g])
		g++;
	return (i + g);
}
