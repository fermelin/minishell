
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
