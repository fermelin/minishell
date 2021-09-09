
#include "minishell.h"

void	output_to_file(t_all *all, char *file_name)
{
	int	fd;

	fd = 0;
	if (all->data->redir == 1)
	{
		if ((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
			return ;
	}
	else if (all->data->redir == 2)
	{
		if ((fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
			return ;
	}
	all->save1_red = dup(1);
	dup2(fd, 1);
	if (close(fd) == -1)
		print_error("close", "fd", strerror(errno));
}

int		input_from_file(t_all *all, char *file_name)
{
	int	fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		print_error(file_name, NULL, strerror(errno));
		all->exit_status = 1;
		return (-1);
	}
	all->save0_red = dup(0);
	dup2(fd, 0);
	if (close(fd) == -1)
		print_error("close", "fd while input_from_file", strerror(errno));
	return (0);
}
