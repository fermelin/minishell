
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*newstr;

	if (!(newstr = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	ft_strlcpy(newstr, s, ft_strlen(s) + 1);
	return (newstr);
}
