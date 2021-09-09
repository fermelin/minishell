
#include "minishell.h"

static	int	is_path_var_not_empty(t_all *all)
{
	char *path;

	path = get_env_str("PATH", all);
	if (path && *path)
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

static	int	find_file_in_path(char *file_name, char **path, t_all *all)
{
	char			*path_slashed;
	char			**splited_path;
	int				env_line;
	int				i;
	struct stat		buf;

	i = 0;
	if ((env_line = get_env_line_nbr("PATH=", all)) == -1)
		return (0);
	splited_path = ft_split(all->env_vars[env_line] + 5, ':');
	while (file_name && *file_name && splited_path && splited_path[i])
	{
		path_slashed = ft_strjoin(splited_path[i], "/");
		*path = ft_strjoin(path_slashed, file_name);
		free(path_slashed);
		if (stat(*path, &buf) == 0)
		{
			free_ptrs_array(splited_path);
			return (1);
		}
		free(*path);
		i++;
	}
	free_ptrs_array(splited_path);
	return (0);
}

static	int	is_exec_file_correct(t_all *all, char **path, char **argv)
{
	struct stat buf;

	if ((ft_strncmp("./", argv[0], 2)) == 0 || (ft_strncmp("../", argv[0], 3))
		== 0 || (ft_strncmp("/", argv[0], 1)) == 0 || stat(argv[0], &buf) == 0)
		*path = argv[0];
	else if (!find_file_in_path(argv[0], path, all))
		*path = NULL;
	if (*path && stat(*path, &buf) == 0)
	{
		if ((buf.st_mode & S_IFDIR) == S_IFDIR)
			print_error_and_exit(*path, "", IS_A_DIR, 126);
		else if ((buf.st_mode & S_IXUSR) != S_IXUSR ||
			(buf.st_mode & S_IRUSR) != S_IRUSR)
			print_error_and_exit(*path, "", strerror(EACCES), 126);
		else
			return (1);
	}
	if ((ft_strncmp("./", argv[0], 2)) == 0 || (ft_strncmp("../", argv[0], 3))
		== 0 || (ft_strncmp("/", argv[0], 1)) == 0 ||
		!is_path_var_not_empty(all))
		print_error(argv[0], "", NO_SUCH_FILE);
	else
		print_error(argv[0], "", CMD_NOT_FOUND);
	exit(127);
}

static	int	child_process(t_all *all, char **argv)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_exec_file_correct(all, &path, argv) == 1)
		execve(path, argv, all->env_vars);
	exit(0);
}

int			exec_cmds(t_all *all, char **argv)
{
	int		status;
	int		pid;

	pid = fork();
	if (pid == 0)
		child_process(all, argv);
	else
	{
		wait(&status);
		if (WIFSIGNALED(status))
		{
			all->child_killed = 1;
			if (WTERMSIG(status) == SIGQUIT)
				ft_putendl_fd(SIGQUIT_TERM, 2);
			return (128 + WTERMSIG(status));
		}
	}
	return (WEXITSTATUS(status));
}
