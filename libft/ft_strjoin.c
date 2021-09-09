
#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !(*s1))
		return (ft_strdup(s2));
	if (!s2 || !(*s2))
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(newstr = (char*)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	ft_strlcpy(newstr, s1, i + 1);
	ft_strlcat(newstr, s2, i + j + 1);
	return (newstr);
}
