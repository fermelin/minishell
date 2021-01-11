/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_and_redirects.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:42:23 by fermelin          #+#    #+#             */
/*   Updated: 2021/01/11 13:11:57 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	filling_struct_elem(int word, char **array, int *choice, t_all *all)
{
	int		j;
	int		g;
	t_data	*last_elem;

	j = 0;
	g = 0;
	last_elem = p_lstlast(all->data);
	while (choice[word] != END)
	{
		if (choice[word] == ARG)
			last_elem->args[j++] = array[word];
		else if (choice[word] == REDIR)
		{
			last_elem->redir_array[g++] = array[word++];
			last_elem->redir_array[g++] = array[word];
		}
		else if (choice[word] == PIPE)
		{
			last_elem->pipe = 1;
			last_elem->next = p_lstnew();
			last_elem->next->pipe_behind = 1;
			break ;
		}
		word++;
	}
}

static void	struct_malloc_and_filling(t_all *all, char **array, int *choice,
	int first_word)
{
	t_data	*last_elem;

	if (all->args_counter != 0 && (last_elem = p_lstlast(all->data)) &&
		!(last_elem->args = ft_calloc(all->args_counter + 1, sizeof(char*))))
		return ;
	if (all->redirs_counter != 0 && (last_elem = p_lstlast(all->data)))
	{
		if (!(last_elem->redir_array =
			ft_calloc(all->redirs_counter + 1, sizeof(char*))))
			return ;
		last_elem->redir = 1;
	}
	filling_struct_elem(first_word, array, choice, all);
	all->redirs_counter = 0;
	all->args_counter = 0;
}

static int	is_argument(t_all *all, char **array, int *j, int *choice)
{
	while (array[(*j)] && what_redirection(array[(*j)]) == 0 &&
		ft_strncmp("|", array[(*j)], 2) != 0)
	{
		choice[(*j)] = ARG;
		all->args_counter++;
		(*j)++;
	}
	return (0);
}

static int	is_redirect(t_all *all, char **array, int *j, int *choice)
{
	while (array[(*j)] && array[(*j) + 1] &&
		what_redirection(array[(*j)]) != 0)
	{
		choice[(*j)] = REDIR;
		all->redirs_counter += 2;
		(*j) += 2;
	}
	return (0);
}

int			split_args_and_redirects(char **array, t_all *all,
	int array_length)
{
	int j;
	int	*choice;
	int	first_word;

	first_word = 0;
	all->redirs_counter = 0;
	all->args_counter = 0;
	if (!(choice = ft_calloc(array_length + 1, sizeof(int))))
		return (print_error("ft_calloc", "", ERR_MALLOC));
	j = 0;
	while (array[j])
	{
		is_argument(all, array, &j, choice);
		is_redirect(all, array, &j, choice);
		if (array[j] && ft_strncmp("|", array[j], 2) == 0)
		{
			choice[j] = PIPE;
			struct_malloc_and_filling(all, array, choice, first_word);
			free(array[j]);
			first_word = ++j;
		}
	}
	struct_malloc_and_filling(all, array, choice, first_word);
	free(choice);
	return (0);
}
