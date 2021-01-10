/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:58:44 by gevelynn          #+#    #+#             */
/*   Updated: 2021/01/11 00:26:40 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*remove_extra_spaces_in_line(char *var)
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

char		*get_env_var_splited(char *str, t_all *all)
{
	char	*var;
	char	*newstr;
	char	*trimmed_var;

	if (!(var = get_env_str(str, all)))
		return (NULL);
	if ((all->params.quotes[1] % 2) || !(trimmed_var = ft_strtrim(var, " \t")))
		return (var);
	if (!(newstr = remove_extra_spaces_in_line(trimmed_var)))
	{
		free(trimmed_var);
		free(var);
		return (NULL);
	}
	free(trimmed_var);
	free(var);
	return (newstr);
}

int			check_dollar(t_all *all, char **word, int start, int *arr)
{
	int		len;
	char	*tmp;
	char	*tempory;

	tempory = NULL;
	tmp = ft_strdup((*word));
	if (((*word)[start]) == '?')
		tempory = ft_itoa(all->exit_status);
	else if (!(tempory = get_env_var_splited((*word) + start, all)))
		tempory = ft_strdup("");
	free(*word);
	(*word) = ft_calloc(arr[1] - arr[0] + start + ft_strlen(tempory) + 1, 1);
	len = -1;
	while (++len < start)
		(*word)[len] = tmp[len];
	ft_strlcat((*word), tempory, ft_strlen(tempory) + ft_strlen(*word) + 1);
	free(tempory);
	free(tmp);
	return (ft_strlen((*word)));
}

void		search_dollar(char **word, char *str, int **start, int *i)
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
		str[(*start)[0]] != ']')
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

char		*search_variable(t_all *all, char **word, char *str, int **start)
{

	initial_params(all, start);
	help_variable(all, word, str, start);
	free_params(all);
	return (str);
}
