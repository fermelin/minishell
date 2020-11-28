/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 13:06:00 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/28 17:04:08 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int			exit_arg_validation(char *arg)
// {
// 	int i;
// 	int sign;

// 	i = 0;
// 	sign = 1;
// 		while (ft_isspace((*args)[i]))
// 			i++;
// 		if ((*args)[i] == '+' || (*args)[i] == '-')
// 		{
// 			sign = ((*args)[i] == '+') ? 1 : -1;
// 			i++;
// 		}
// 		while (ft_isdigit((*args)[i]))
// 			i++;

// }

int			ft_exit(char **args)
{
	int exit_status;
	int i;

	if (*args)
	{
		if (*(args + 1))
		{
			print_error("exit", "", TOO_MANY_ARGS);
			exit (1);
		}
		i = 0;
		while (ft_isspace((*args)[i]))
			i++;
		if ((*args)[i] == '+' || (*args)[i] == '-')
			i++;
		if ((exit_status = ft_atoi(*args)) == 0)
		{
			if ((*args)[i] == '0')
				exit (0);
			print_error("exit", *args, NUM_ARG_NEEDED);
			exit (255);
		}
		while (ft_isdigit((*args)[i]))
			i++;
		while (ft_isspace((*args)[i]))
			i++;
		if ((*args)[i] != '\0')
		{
			print_error("exit", *args, NUM_ARG_NEEDED);
			exit (255);
		}
	}
	else
		exit(0);
	exit(exit_status);
}

static int		is_string_consists_only_one_char(char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] == c)
		i++;
	if (!str[i])
		return (1);
	return (0);
}


int		ft_echo(char **args)
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