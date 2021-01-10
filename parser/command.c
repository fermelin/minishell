/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:06:35 by gevelynn          #+#    #+#             */
/*   Updated: 2021/01/10 20:38:07 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				error_quotes(t_all *all, char *line)
{
	int i;
	int	one_quote;
	int	two_quote;

	i = 0;
	one_quote = 0;
	two_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			counting_quotes(line, &one_quote, &two_quote, i);
		i++;
	}
	if (one_quote % 2 != 0 || two_quote % 2 != 0)
	{
		if (one_quote % 2 != 0)
			print_error_with_arg(ERR_QUOTE, "\'", NULL);
		else
			print_error_with_arg(ERR_QUOTE, "\"", NULL);
		all->exit_status = 2;
		return (-1);
	}
	return (0);
}

int				first_check_syntax_error(char *line, t_all *all)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == ';' || line[i] == '|')
	{
		if (line[i] == ';')
			print_error_with_arg(SYNTAX_ERROR, ";", NULL);
		else
			print_error_with_arg(SYNTAX_ERROR, "|", NULL);
		all->exit_status = 2;
		return (-1);
	}
	if (error_quotes(all, line) == -1)
		return (-1);
	return (0);
}

static	int		is_argument_exists(char *str, int start, int end)
{
	int i;

	i = start;
	while (i < end)
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int				syntax_check(t_all *all, char *str, int **arr, t_list **new)
{
	char		*word;
	t_list		*temp;

	if (is_argument_exists(str, (*arr)[0], (*arr)[1]))
	{
		if (!(word = ft_calloc(((*arr)[1] + 1) - (*arr)[0], sizeof(char))))
			return (print_error("ft_calloc", "", ERR_MALLOC));
		search_variable(all, &word, str, arr);		//!!!!!!!!!!! why does it return str???
		temp = ft_lstnew(word);
		ft_lstadd_back(new, temp);
	}
	return (0);
}

int				check_conditions_for_start_arg_processing(char *str, int *arr, int *quotes)
{
	if ((str[arr[1]] == ' ' || str[arr[1]] == '\t' || str[arr[1]] == '|'
		|| str[arr[1]] == '>' || str[arr[1]] == '<') &&
		str[arr[1] - 1] != '\\' && quotes[0] % 2 == 0 && quotes[1] % 2 == 0)
		return (1);
	return (0);
}

int				arguments_search(char *str, t_all *all)
{
	int			*arr;
	int			*quotes;
	t_list		*new;
	int			is_syntax_error;

	new = NULL;
	if (!(arr = ft_calloc(2, sizeof(int))) ||
		!(quotes = ft_calloc(2, sizeof(int))))
		return (-1);
	while (str[arr[1]])
	{
		if (str[arr[1]] == '\'' || str[arr[1]] == '\"')
			counting_quotes(str, &(quotes[0]), &(quotes[1]), arr[1]);
		else if (check_conditions_for_start_arg_processing(str, arr, quotes))
			help_arguments(all, &str, &arr, &new);
		arr[1]++;
	}
	syntax_check(all, str, &arr, &new);
	is_syntax_error = filling_struct(all, new, ft_lstsize(new));
	ft_lstclear(&new, NULL);
	free(arr);
	free(quotes);
	return (is_syntax_error);
}

static void	line_trim(char *line, int *start, int *end)
{
	while (line[*start] == ' ' || line[*start] == '\t')
		(*start)++;
	while (((line[*end] == ' ' && line[*end - 1] != '\\') ||
				line[*end] == '\t') && *end != 0)
		(*end)--;
	if (line[*end] != ' ' || line[*end] != '\t')
		(*end)++;
	if (line[*start] == '\0')
		*start = 0;
}

// строка для обработки
int				line_search(char *line, t_all *all, int start, int end)
{
	char		*str;
	int			j;
	int			is_syntax_error;

	is_syntax_error = 0;
	all->data = p_lstnew();
	if (line[end + 1] && line[end + 1] == ';')
		all->is_semicolon = 1;
	if (end >= start)
	{
		line_trim(line, &start, &end);
		if (!(str = (char *)malloc(sizeof(char) * ((end + 1) - (start--))))) // почистить
			return (print_error("malloc", "", ERR_MALLOC));
		j = -1;
		while (++start < end)
			str[++j] = line[start];
		str[j + 1] = '\0';
		is_syntax_error = arguments_search(str, all);
		free(str);
	}
	return (is_syntax_error);
}
