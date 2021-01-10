/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:02:13 by gevelynn          #+#    #+#             */
/*   Updated: 2021/01/10 16:27:57 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	filling_struct_elem(int word, char **array, int *choice, t_all *all)
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

void	allocate_memory_for_struct(t_all *all, int args_count, int redirs_count)
{
	t_data	*last_elem;

	if (args_count != 0 && (last_elem = p_lstlast(all->data)) && !(last_elem->args = ft_calloc(args_count + 1, sizeof(char*))))
		return ;
	if (redirs_count != 0 && (last_elem = p_lstlast(all->data)))
	{
		if (!(last_elem->redir_array = ft_calloc(redirs_count + 1, sizeof(char*))))
			return ;
		last_elem->redir = 1;
	}
}

int	*split_args_and_redirects(char **array, t_all *all, int	array_length)
{
	int j;
	int	redirs_count;
	int	args_count;
	int	*choice;
	int	first_word;
	enum	e_type;

	first_word = 0;
	redirs_count = 0;
	args_count = 0;
	if (!(choice = ft_calloc(array_length + 1, sizeof(int))))
		return (0);									//error handling
	j = 0;
	while (array[j])
	{
		while (array[j] && what_redirection(array[j]) == 0 && ft_strncmp("|", array[j], 2) != 0)
		{
			choice[j] = ARG;
			args_count++;
			j++;
		}
		while (array[j] && array[j + 1] && what_redirection(array[j]) != 0)
		{
			choice[j] = REDIR;
			j += 2;
			redirs_count += 2;
		}
		if (array[j] && ft_strncmp("|", array[j], 2) == 0)
		{
			allocate_memory_for_struct(all, args_count, redirs_count);
			choice[j] = PIPE;
			filling_struct_elem(first_word, array, choice, all);
			free(array[j]);
			first_word = ++j;
			redirs_count = 0;
			args_count = 0;
		}
	}
	allocate_memory_for_struct(all, args_count, redirs_count);
	filling_struct_elem(first_word, array, choice, all);
	return (choice);
}

int		is_special_symbol(t_all *all, char *str)
{
	if (str == NULL && all->is_semicolon)
		return (1);
	else if (what_redirection(str) != 0 || ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}

int		check_syntax_error(t_all *all, char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (is_special_symbol(all, array[i]) != 0 && array[i + 1] &&
			is_special_symbol(all, array[i + 1]) != 0)
		{
			print_error_with_arg(SYNTAX_ERROR, array[i + 1], NULL);
		}
		else if (what_redirection(array[i]) != 0 && array[i + 1] == NULL)
		{
			if (all->is_semicolon == 1)
			{
				all->is_semicolon = 0;
				print_error_with_arg(SYNTAX_ERROR, ";", NULL);
			}
			else
				print_error_with_arg(SYNTAX_ERROR, "newline", NULL);
		}
		else
			continue ;
		break ;
	}
	if (array[i] != NULL)
	{
		all->exit_status = 2;
		return (-1);
	}
	return (0);
}

int		filling_struct(t_all *all, t_list *new, int len)
{
	t_list	*new_copy;
	char	**array;
	int		*choice;
	int		i;

	i = 0;
	new_copy = new;
	array = ft_calloc(len + 1, sizeof(char *));		//temp->args = (char **)malloc(sizeof(char*) * (len + 1)) 
	while(new_copy)
	{
		array[i] = new_copy->content;
		new_copy = new_copy->next;
		i++;
	}
	if (check_syntax_error(all, array) != -1)
	{
		choice = split_args_and_redirects(array, all, len);
		free(choice);										// delete this shit
		free(array);
	}
	else
	{
		free(array);
		return (-1);
	}
	return (0);
	
}
