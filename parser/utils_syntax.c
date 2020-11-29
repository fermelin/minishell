/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:58:44 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/29 20:18:06 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

// int        check_dollar(t_all *all, char **word, int i)
// {
//     int        start;
//     int        len;
//     char    *tmp;
//     char     ch;
//     char    *tempory = NULL; //временная
//     int    check; //для случая когда запись переменной окружения больше его значения

//     // printf("%s\n", (*word));
//     check = -1;
//     start = i++; // начало переменной (место $)
//     while ((*word)[i] && (*word)[i] != '\'' && (*word)[i] != '\"' && (*word)[i] != ' ' && (*word)[i] != '$')
//         i++; // конец переменной
//     tmp = ft_strdup((*word)); //сохранили слово
//     ch = (*word)[i]; // сохранили символ конца переменной
//     (*word)[i] = '\0'; // заменили на символ конца строки, что узнать длину переменной окружения
//     if (!(tempory = get_env_str(((*word) + (start + 1)), all)))
//         tempory = ft_strdup(""); //почистить
//     len = ft_strlen(tempory);
//     if ((size_t)len < ft_strlen(*word))
//         check = 0;
//     free((*word));
//     (*word) = ft_calloc(ft_strlen(tmp) + 1 + len - (i - start), sizeof(char)); // выделили новую память с учетом переменной окружения
//     len = -1; // больше не нужна, можно использовать
//     while(++len < start)
//         (*word)[len] = tmp[len]; // копируем строку обратно в (*word) до знака $
//     // после того как дошли до доллара, то вместо названия переменной окружения добавали путь
//     ft_strlcat((*word), tempory, ft_strlen(tempory) + ft_strlen(*word) + 1);
//     if (tempory[0] == '\0')
//         free(tempory);
//     len = ft_strlen((*word));
//     (*word)[start + len] = ch; // вернули сохраненый символ строка 14;
//     start = i;
//     while (tmp[start])
//         (*word)[len++] = tmp[start++];
//     if (check == 0)
//         return (0);
//     return (i);
// }

// char		*search_variable(t_all *all, char **word)
// {
// 	int		i;
// 	int		one_quotes;

// 	i = 0;
// 	one_quotes = 0;
// 	while ((*word)[i])
// 	{
// 		if ((*word)[i] == '\'' || (*word)[i] == '\"' || (*word)[i] == '\\')
// 		{
// 			if ((*word)[i] == '\'')
// 				one_quotes++;
// 			i = delete_symbol(&(*word), i, (*word)[i]);\
// 		}
// 		else if ((*word)[i] == '$' && one_quotes % 2 == 0 && (*word)[i - 1] != '\\' &&
// 				(ft_isalnum((*word)[i + 1]) || (*word)[i + 1] == '_'))
// 		// {
// 		// 	printf("GOOD\n");
// 		// 	printf("%s\n", (*word));
// 		// 	printf("%d\n", i);
// 			i = check_dollar(all, &(*word), i); //функция должна вернуть int (то есть с какого места продолжаем парсить строку)
// 		// }
// 		else
// 			i++;
// 	}
// 	return ((*word));
// }

int         check_dollar(t_all *all, char **word, int i, int *arr)
{
	int     len;
	char    *tmp;
	char    *tempory = NULL; //временная
	int     question_mark;

	question_mark = 0;
	tmp = ft_strdup((*word)); //сохранили слово
	if (((*word)[i]) == '?')
	{
		question_mark = 1;
		tempory = ft_itoa(all->exit_status);
	}
	else if (!(tempory = get_env_str(((*word) + i), all)))
		tempory = ft_strdup(""); //почистить
	len = ft_strlen(tempory);
	free(*word);
	*word = NULL;
	(*word) = ft_calloc((arr[1] - arr[0]) + len + 1, sizeof(char)); // выделили новую память с учетом переменной окружения
	len = -1;
	while(++len < i)
		(*word)[len] = tmp[len]; // копируем строку обратно в (*word) до знака $
		// после того как дошли до доллара, то вместо названия переменной окружения добавали путь
	ft_strlcat((*word), tempory, ft_strlen(tempory) + ft_strlen(*word) + 1);
	free(tempory);
	len = ft_strlen((*word));
	free(tmp);
	return (len);
}

// start[0] и start[1] начало и конец аргумента по строке str
void    search_variable(t_all *all, char **word, char *str, int *start)
{
	int     i;
	int     one_quotes;
	int     two_quotes;
	int     check;  // для переменной окружения
	int     num;  // для обработки $1234 вот такого случая с оригинальным bash
	int		arr[2]; 

	i = 0;
	one_quotes = 0;
	two_quotes = 0;
	arr[0] = start[0];
	arr[1] = start[1];

	while (start[0] < start[1])
	{
		//------------------------------------------------------------
		if (str[start[0]] == '$' && !(one_quotes % 2) && (ft_isalnum(str[start[0] + 1]) ||
			str[start[0] + 1] == '_' || str[start[0] + 1] == '?'))
		{
			num = start[0];
			check = i; //запомнили место куда будет переписана переменная окружения в word
			start[0]++;
			while (str[start[0]] && str[start[0]] != '\'' && str[start[0]] != '\"' && str[start[0]] != ' ' &&
				str[start[0]] != '$' && str[start[0]] != '\\')
			{
				if (str[num] == '$' && ((ft_isdigit(str[num + 1]) && ft_isdigit(str[num + 2])) || str[num + 1] == '?'))
				{
					(*word)[i] = str[start[0]];
					(*word)[i++] = str[start[0]++];
					break ;
				}
				(*word)[i] = str[start[0]];
				start[0]++;
				i++;
			}
			i = check_dollar(all, word, check, arr); //возвращает длину строки word  с подставленной переменной окружения
			start[0]--;
			i--;
		}
		//------------------------------------------------------------
		else if (str[start[0]] == '\\')
		{
			if (!(one_quotes % 2) && !(two_quotes % 2))
				(*word)[i] = str[++start[0]];
			else if (one_quotes % 2 && !(two_quotes % 2))
				(*word)[i] = str[start[0]];
			else if (!(one_quotes % 2) && two_quotes % 2)
			{
				if (str[start[0] + 1] == '$' || str[start[0] + 1] == '\\' || str[start[0] + 1] == '\"')
					(*word)[i] = str[++start[0]];
				else
					(*word)[i] = str[start[0]];
			}
		}
		else if(str[start[0]] == '\"')
		{
			two_quotes++;
			if(one_quotes % 2)
			{
				(*word)[i] = str[start[0]];
				two_quotes++;
			}
			else if (!(one_quotes % 2))
				i--;
		}
		else if(str[start[0]] == '\'')
		{
			one_quotes++;
			if(two_quotes % 2 || (str[i - 1] == '\\'))
			{
				(*word)[i] = str[start[0]];
				one_quotes++;
			}
			else if (!(two_quotes % 2))
				i--;
		}
		else 
			(*word)[i] = str[start[0]];
		start[0]++;
		i++;
	}
	(*word)[i + 1] = '\0';
	// return ((*word));
}







