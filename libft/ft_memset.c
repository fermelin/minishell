
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	c1;

	i = 0;
	s1 = (unsigned char*)s;
	c1 = (unsigned char)c;
	while (i < n)
	{
		s1[i] = c1;
		i++;
	}
	return (s);
}
