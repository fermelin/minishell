
#include "libft.h"

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		;
	else
		while (s[start + i] && i < len)
			i++;
	if (!(newstr = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	while (j < i)
	{
		newstr[j] = s[start + j];
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}
