/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 13:20:32 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/09 18:58:02 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static	int		result_with_n(char **line, char **archive, char *n_ptr)
{
	char	*temp;

	*n_ptr = '\0';
	*line = ft_strdup(*archive);
	n_ptr++;
	temp = ft_strdup(n_ptr);
	free(*archive);
	*archive = temp;
	return (1);
}

static	int		result_without_n(char **line, char **archive, int ret)
{
	char	*n_ptr;

	if (ret == -1)
		return (-1);
	if (*archive && (n_ptr = ft_strchr(*archive, '\n')))
		return (result_with_n(line, archive, n_ptr));
	if (*archive)
	{
		*line = *archive;
		*archive = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int			ret;
	char		*buf;
	static char	*archive;
	char		*n_ptr;

	if (BUFFER_SIZE < 1 || fd < 0 || !line || read(fd, archive, 0) != 0 ||
		!(buf = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		archive = ft_strjoin_free(archive, buf);
		ft_putstr_fd("  \b\b", 1);					//solve it
		if ((n_ptr = ft_strchr(archive, '\n')))
		{
			free(buf);
			return (result_with_n(line, &archive, n_ptr));
		}
	}
	free(buf);
	return (result_without_n(line, &archive, ret));
}
