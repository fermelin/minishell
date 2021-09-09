
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	c2;

	i = 0;
	c2 = (unsigned char)c;
	while (i < n)
	{
		if (((unsigned char*)s)[i] == c2)
			return ((void*)s + i);
		i++;
	}
	return (NULL);
}
