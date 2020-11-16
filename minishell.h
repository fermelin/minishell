/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:27:00 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/13 19:28:07 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "./libft/libft.h"


typedef	struct s_all
{
	char	**env_vars;
	size_t	env_amount;
}				t_all;

int		ft_cd(char *path, t_all *all);
int		ft_pwd(void);
void	ft_env(t_all *all);
void	ft_unset(t_all *all, char **args);
void	ft_export(t_all *all, char **args);

void	free_ptrs_array(char **ptr_array);

#endif
