
#include "minishell.h"

static	int		check_conditions_for_start_arg_processing(char *str,
	int *arr, int *quotes)
{
	if ((str[arr[1]] == ' ' || str[arr[1]] == '\t' || str[arr[1]] == '|'
		|| str[arr[1]] == '>' || str[arr[1]] == '<') &&
		quotes[0] % 2 == 0 && quotes[1] % 2 == 0)
	{
		if (arr[1] != 0 && str[arr[1] - 1] != '\\')
			return (1);
		else if (arr[1] == 0)
			return (1);
	}
	return (0);
}

static	int		arguments_search(char *str, t_all *all)
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

static void		line_trim(char *line, int *start, int *end)
{
	while (line[*start] == ' ' || line[*start] == '\t')
		(*start)++;
	while (((line[*end] == ' ' || line[*end] == '\t') &&
		((*end != 0 && line[*end - 1] != '\\') || *end == 0)))
		(*end)--;
	if (line[*end] != ' ' || line[*end] != '\t')
		(*end)++;
	if (line[*start] == '\0')
		*start = 0;
}

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
		if (!(str = (char *)malloc(sizeof(char) * ((end + 1) - (start--)))))
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
