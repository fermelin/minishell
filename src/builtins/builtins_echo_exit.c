
#include "minishell.h"

static	void	print_exit_or_not(int whence_the_command)
{
	if (whence_the_command == 0)
		ft_putendl_fd("exit", 2);
}

static	void	exit_arg_validation(char *args, int *exit_status,
	int whence_the_command)
{
	int i;

	i = 0;
	while (ft_isspace(args[i]))
		i++;
	if (args[i] == '+' || args[i] == '-')
		i++;
	if ((*exit_status = ft_atoi(args)) == 0)
	{
		print_exit_or_not(whence_the_command);
		if (args[i] == '0')
			exit(0);
		print_error_and_exit("exit", args, NUM_ARG_REQUIRED, 255);
	}
	while (ft_isdigit(args[i]))
		i++;
	while (args[i] == ' ' || args[i] == '\t')
		i++;
	if (args[i] != '\0')
	{
		print_exit_or_not(whence_the_command);
		print_error_and_exit("exit", args, NUM_ARG_REQUIRED, 255);
	}
}

int				ft_exit(char **args, t_all *all)
{
	int exit_status;

	if (*args)
	{
		if (*(args + 1))
		{
			print_exit_or_not(all->whence_the_command);
			print_error("exit", "", TOO_MANY_ARGS);
			return (1);
		}
		exit_arg_validation(*args, &exit_status, all->whence_the_command);
	}
	else
		exit_status = all->exit_status;
	print_exit_or_not(all->whence_the_command);
	exit(exit_status);
}

static	int		is_string_consists_only_one_char(char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int				ft_echo(char **args)
{
	size_t	i;
	int		n_flag;

	n_flag = 0;
	if (args)
	{
		i = 0;
		while (args[i] && ft_strncmp("-n", args[i], 2) == 0 && (!args[i][2] ||
			is_string_consists_only_one_char(&args[i][2], 'n')))
		{
			n_flag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			i++;
			if (args[i])
				ft_putchar_fd(' ', 1);
		}
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
