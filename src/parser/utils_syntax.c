
#include "minishell.h"

static	char	*remove_extra_spaces_in_line(char *var)
{
	char	*newstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(newstr = (char*)malloc(sizeof(char) * (ft_strlen(var) + 1))))
		return (NULL);
	while (var[i])
	{
		if (ft_isspace(var[i]))
		{
			newstr[j++] = var[i];
			while (ft_isspace(var[i]))
				i++;
		}
		else
			newstr[j++] = var[i++];
	}
	newstr[j] = '\0';
	return (newstr);
}

static	char	*get_env_var_splited(char *str, t_all *all)
{
	char	*var;
	char	*newstr;
	char	*trimmed_var;

	newstr = NULL;
	if (!(var = get_env_str(str, all)))
		return (NULL);
	if ((all->params.quotes[1] % 2) || !(trimmed_var = ft_strtrim(var, " \t")))
		return (var);
	if (all->params.quotes[1] % 2 == 0)
	{
		if (!(newstr = remove_extra_spaces_in_line(trimmed_var)))
		{
			free(trimmed_var);
			free(var);
			return (NULL);
		}
	}
	else
		return (var);
	free(trimmed_var);
	free(var);
	return (newstr);
}

static	int		check_dollar(t_all *all, char **word, int start, int *arr)
{
	int		len;
	char	*tmp;
	char	*tempory;

	tempory = NULL;
	tmp = ft_strdup((*word));
	if (((*word)[start]) == '?')
		tempory = ft_itoa(all->exit_status);
	else if (!(tempory = get_env_var_splited((*word) + start, all)))
	{
		all->empty_env_var = 1;
		tempory = ft_strdup("");
	}
	free(*word);
	if (!((*word) = ft_calloc(arr[1] - arr[0] + start +
		ft_strlen(tempory) + 1, sizeof(char))))
		return (0);
	len = -1;
	while (++len < start)
		(*word)[len] = tmp[len];
	ft_strlcat((*word), tempory, ft_strlen(tempory) + ft_strlen(*word) + 1);
	free(tempory);
	free(tmp);
	return (ft_strlen((*word)));
}

static	void	search_dollar(char **word, char *str, int **start, int *i)
{
	int		num;
	int		check;

	num = (*start)[0];
	check = *i;
	(*start)[0]++;
	while (str[(*start)[0]] && str[(*start)[0]] != '\'' &&
		str[(*start)[0]] != '\"' && str[(*start)[0]] != ' ' &&
		str[(*start)[0]] != '$' && str[(*start)[0]] != '\\' &&
		str[(*start)[0]] != '=' && str[(*start)[0]] != '|' &&
		str[(*start)[0]] != ']' && str[(*start)[0]] != ',')
	{
		if (str[num] == '$' && ((ft_isdigit(str[num + 1]) &&
			ft_isdigit(str[num + 2])) || str[num + 1] == '?'))
		{
			(*word)[*i] = str[(*start)[0]];
			(*word)[(*i)++] = str[(*start)[0]++];
			break ;
		}
		(*word)[(*i)] = str[(*start)[0]];
		(*start)[0]++;
		(*i)++;
	}
	*i = check;
}

void			search_variable(t_all *all, char **word, char *str, int **start)
{
	initial_params(all, start);
	while ((*start)[0] < (*start)[1])
	{
		if (str[(*start)[0]] == '$' && !(all->params.quotes[0] % 2) &&
			(ft_isalnum(str[(*start)[0] + 1]) ||
			str[(*start)[0] + 1] == '_' || str[(*start)[0] + 1] == '?'))
		{
			search_dollar(word, str, start, &(all->params.i));
			all->params.i = check_dollar(all, word,
							all->params.i, all->params.arr);
			(*start)[0]--;
			all->params.i--;
		}
		else if (str[(*start)[0]] == '\\')
			dash(all, word, str, start);
		else if (str[(*start)[0]] == '\"')
			two_quotes(all, word, str, start);
		else if (str[(*start)[0]] == '\'')
			one_quotes(all, word, str, start);
		else
			(*word)[all->params.i] = str[(*start)[0]];
		(*start)[0]++;
		all->params.i++;
	}
}
