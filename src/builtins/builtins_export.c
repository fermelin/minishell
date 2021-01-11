/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:34:56 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/11 12:46:34 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	env_vars_sort(t_all *all, int **mass)
{
	int		i;
	size_t	len;
	int		tmp;

	i = 0;
	while (i < (int)all->env_amount - 2)
	{
		len = ft_strlen(all->env_vars[(*mass)[i]]) + 1;
		if (ft_strncmp(all->env_vars[(*mass)[i]],
			all->env_vars[(*mass)[i + 1]], len) > 0)
		{
			tmp = (*mass)[i + 1];
			(*mass)[i + 1] = (*mass)[i];
			(*mass)[i] = tmp;
			i = -1;
		}
		i++;
	}
}

static	int		export_arg_validation(char *arg, int *exit_status)
{
	size_t i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalpha(arg[i]) || (ft_isdigit(arg[i]) && i != 0) ||
			arg[i] == '_')
			i++;
		else
			break ;
	}
	if ((arg[i] == '\0' || arg[i] == '=') && i != 0)
		return (0);
	print_error_with_arg("export", arg, NOT_VALID_ID);
	*exit_status = 1;
	return (1);
}

static	int		export_without_args(t_all *all)
{
	int		*mass;
	size_t	i;

	if (!(mass = (int *)malloc(sizeof(int) * all->env_amount + 1)))
		return (-1);
	i = 0;
	while (i < all->env_amount)
	{
		mass[i] = i;
		i++;
	}
	env_vars_sort(all, &mass);
	print_export_without_args(all, mass);
	free(mass);
	return (0);
}

int				ft_export(t_all *all, char **args)
{
	char	*equal_sign_ptr;
	int		shift;
	char	*key;
	int		exit_status;

	exit_status = 0;
	if ((!args || !(*args)) && export_without_args(all) == -1)
		return (1);
	else
		while (*args)
		{
			if ((export_arg_validation(*args, &exit_status) == 0) &&
				(equal_sign_ptr = ft_strchr(*args, '='))
				&& equal_sign_ptr != *args)
			{
				shift = equal_sign_ptr - *args + 1;
				if (!(key = (char *)malloc(sizeof(char) * (shift + 1))))
					return (1);
				ft_strlcpy(key, *args, shift + 1);
				edit_or_add_env_line(key, &((*args)[shift]), all);
				free(key);
			}
			args++;
		}
	return (exit_status);
}
