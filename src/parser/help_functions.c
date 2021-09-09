
#include "minishell.h"

static	int	is_argument_exists(char *str, int start, int end)
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

int			syntax_check(t_all *all, char *str, int **arr, t_list **new)
{
	char		*word;
	t_list		*temp;

	if (is_argument_exists(str, (*arr)[0], (*arr)[1]))
	{
		all->empty_env_var = 0;
		if (!(word = ft_calloc(((*arr)[1] + 1) - (*arr)[0], sizeof(char))))
			return (print_error("ft_calloc", "", ERR_MALLOC));
		search_variable(all, &word, str, arr);
		if (word && all->empty_env_var == 0)
		{
			if ((temp = ft_lstnew(word)))
				ft_lstadd_back(new, temp);
		}
		else
			free(word);
	}
	return (0);
}

void		help_arguments(t_all *all, char **str, int **arr, t_list **new)
{
	if (((*str)[(*arr)[0]] != '>' && (*str)[(*arr)[0]] != '<' &&
		(*str)[(*arr)[0]] != '|'))
		syntax_check(all, *str, arr, new);
	while ((*str)[(*arr)[1]] == ' ' || (*str)[(*arr)[1]] == '\t')
	{
		(*arr)[1]++;
		(*arr)[0] = (*arr)[1];
	}
	if ((*str)[(*arr)[1]] == '>' || (*str)[(*arr)[1]] == '<' ||
		(*str)[(*arr)[1]] == '|')
	{
		(*arr)[0] = (*arr)[1];
		(*arr)[1]++;
		if ((*str)[(*arr)[1]] == '>')
			(*arr)[1]++;
		syntax_check(all, *str, arr, new);
		(*arr)[0] = (*arr)[1];
	}
	while ((*str)[(*arr)[1]] == ' ' || (*str)[(*arr)[1]] == '\t')
	{
		(*arr)[1]++;
		(*arr)[0] = (*arr)[1];
	}
	(*arr)[1]--;
}
