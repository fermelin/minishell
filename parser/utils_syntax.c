/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:58:44 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/28 13:25:11 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int        check_dollar(t_all *all, char **word, int i)
{
    int        start;
    int        len;
    char    *tmp;
    char     ch;
    char    *tempory = NULL; //временная
    int    check; //для случая когда запись переменной окружения больше его значения

    // printf("%s\n", (*word));
    check = -1;
    start = i++; // начало переменной (место $)
    while ((*word)[i] && (*word)[i] != '\'' && (*word)[i] != '\"' && (*word)[i] != ' ' && (*word)[i] != '$')
        i++; // конец переменной
    tmp = ft_strdup((*word)); //сохранили слово
    ch = (*word)[i]; // сохранили символ конца переменной
    (*word)[i] = '\0'; // заменили на символ конца строки, что узнать длину переменной окружения
    if (!(tempory = get_env_str(((*word) + (start + 1)), all)))
        tempory = ft_strdup(""); //почистить
    len = ft_strlen(tempory);
    if ((size_t)len < ft_strlen(*word))
        check = 0;
    free((*word));
    (*word) = ft_calloc(ft_strlen(tmp) + 1 + len - (i - start), sizeof(char)); // выделили новую память с учетом переменной окружения
    len = -1; // больше не нужна, можно использовать
    while(++len < start)
        (*word)[len] = tmp[len]; // копируем строку обратно в (*word) до знака $
    // после того как дошли до доллара, то вместо названия переменной окружения добавали путь
    ft_strlcat((*word), tempory, ft_strlen(tempory) + ft_strlen(*word) + 1);
    if (tempory[0] == '\0')
        free(tempory);
    len = ft_strlen((*word));
    (*word)[start + len] = ch; // вернули сохраненый символ строка 14;
    start = i;
    while (tmp[start])
        (*word)[len++] = tmp[start++];
    if (check == 0)
        return (0);
    return (i);
}

char		*search_variable(t_all *all, char **word)
{
	int		i;
	int		one_quotes;

	i = 0;
	one_quotes = 0;
	while ((*word)[i])
	{
		if ((*word)[i] == '\'' || (*word)[i] == '\"' || (*word)[i] == '\\')
		{
			if ((*word)[i] == '\'')
				one_quotes++;
			i = delete_symbol(&(*word), i, (*word)[i]);\
		}
		else if ((*word)[i] == '$' && one_quotes % 2 == 0 && (*word)[i - 1] != '\\' &&
				(ft_isalnum((*word)[i + 1]) || (*word)[i + 1] == '_'))
		// {
		// 	printf("GOOD\n");
		// 	printf("%s\n", (*word));
		// 	printf("%d\n", i);
			i = check_dollar(all, &(*word), i); //функция должна вернуть int (то есть с какого места продолжаем парсить строку)
		// }
		else
			i++;
	}
	return ((*word));
}
