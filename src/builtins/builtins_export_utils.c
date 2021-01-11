/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:34:16 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/11 12:56:14 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		is_escape_symbol(char c)
{
	if (c == '\\' || c == '\"' || c == '$')
		return (1);
	return (0);
}

static	void	print_export_var_key(char *env_var, size_t *j)
{
	ft_putstr_fd("declare -x ", 1);
	while (env_var[(*j)] &&
		(((*j) != 0 && env_var[(*j) - 1] != '=') || (*j) == 0))
		(*j)++;
	write(1, env_var, (*j));
	write(1, "\"", 1);
}

void			print_export_without_args(t_all *all, int *mass)
{
	size_t	i;
	size_t	j;
	char	*env_var;

	i = 0;
	while (i < all->env_amount)
	{
		j = 0;
		print_export_var_key(all->env_vars[mass[i]], &j);
		while (all->env_vars[mass[i]][j])
		{
			env_var = &all->env_vars[mass[i]][j];
			while (all->env_vars[mass[i]][j] &&
				is_escape_symbol(all->env_vars[mass[i]][j]) != 1)
				j++;
			if (is_escape_symbol(all->env_vars[mass[i]][j]) == 1)
			{
				write(1, "\\", 1);
				j++;
			}
			write(1, env_var, &all->env_vars[mass[i]][j] - env_var);
		}
		write(1, "\"\n", 2);
		i++;
	}
}
