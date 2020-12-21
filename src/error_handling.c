/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 06:05:34 by fermelin          #+#    #+#             */
/*   Updated: 2020/12/21 20:37:05 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(char *text_error)
{
	ft_putstr_fd(text_error, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

void	print_unset_error(char *command, char *argument, char *error_message)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("`", 2);
	if (argument && *argument)
		ft_putstr_fd(argument, 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_message, 2);
}

void	print_error(char *command, char *argument, char *error_message)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	if (argument && *argument)
	{
		ft_putstr_fd(argument, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error_message, 2);
}