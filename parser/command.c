#include "libft.h"
#include "minishell.h"

// // сдвиг строки на один символ
// void line_shift(char **str, int j)
// {
// 	while((*str)[++j])
// 		(*str)[j] = (*str)[j + 1];
// }

// int delete_symbol(char **str, int i, char c)
// {
//     int flag;
//     int check; //для запоминания переменной окружения

//     check = -1;
//     flag = 0;
//     if (c == '\"') // для экранирования специальных символом $\"
//         flag = 1;
//     if (c == '\\')
//         line_shift(str, ((i++) - 1));
//     else
//     {
//         line_shift(str, (i - 1));
//         while ((*str)[i] != c && ((*str)[i]))
//         {
//             //для обработки доллара
//             if ((*str)[i] == '$' && (*str)[i - 1] != '\\' &&
//                 (ft_isalnum((*str)[i + 1]) || (*str)[i + 1] == '_'))
//                 check = i;
//             // -------------------------------------------------------
//             if (flag == 1 && (*str)[i] == '\\' && ((*str)[i + 1] == '$' ||
//                 (*str)[i + 1] == '\\' || (*str)[i + 1] == '\"'))
//                 line_shift(str, (i - 1));
//             i++;
//         }
//         if ((*str)[i] != c)
//             (*str)[i] = c;
//         line_shift(str, (i - 1));
//     }
//     if (check > -1)
//         return (check);
//     return (i);
// }

// // убираем кавычки, согласно синтаксису bash
// void			syntax_check(t_all *all, char *str, int *arr, t_list **new)
// {
// 	int			i;
// 	char		*word;
// 	t_list		*temp;

// 	i = -1;
// 	temp = *new;
// 	if (!(word = (char *)malloc(sizeof(char) * ((arr[1] + 1) - (arr[0]--))))) // почистить
// 		return (error_malloc());
// 	while (++arr[0] < arr[1])
// 		word[++i] = str[arr[0]];
// 	word[i + 1] = '\0';
// 	word = search_variable(all, &word);
// 	if (temp->content == NULL)
// 		temp->content = word;
// 	else
// 		ft_lstadd_back(&temp, ft_lstnew(word));
// }

// убираем кавычки, согласно синтаксису bash
void			syntax_check(t_all *all, char *str, int *arr, t_list **new)
{
	int			i;
	char		*word = NULL;
	// t_list		*temp;

	i = -1;
	// temp = *new;
	if (!(word = ft_calloc((arr[1] + 1) - arr[0], sizeof(char)))) // почистить
		return (error_malloc());
	search_variable(all, &word, str, arr);
	if ((*new)->content == NULL)
		(*new)->content = word;
	else
		ft_lstadd_back(new, ft_lstnew(word));
}



void			arguments_search(char *str, t_all *all)
{
	int			arr[2];
	int			one_quotes;
	int			two_quotes;
	t_list		*new = NULL;

	arr[0] = 0;
	arr[1] = -1;
	one_quotes = 0;
	two_quotes = 0;
	new = ft_lstnew(NULL);
	while (str[++arr[1]])
	{
		// последние два условия для корректной обработки аргументов при экранировании (например, \'\"\\ "\hello\$PWD")
		if(str[arr[1]] == '\'')
			one_quotes = counting_quotes(str, one_quotes, two_quotes, arr[1]);
		else if(str[arr[1]] == '\"')
			two_quotes = counting_quotes(str, one_quotes, two_quotes, arr[1]);
		else if (str[arr[1]] == ' ' && one_quotes % 2 == 0 && two_quotes % 2 == 0)
		{
			syntax_check(all, str, arr, &new);
			while (str[arr[1]++] == ' ')
				arr[0] = arr[1];
			arr[1] = arr[0] - 1;
		}
	}
	syntax_check(all, str, arr, &new);
	filling_struct(all, new, ft_lstsize(new));
	ft_lstclear(&new, NULL);
}

// строка для обработки
void			line_search(char *line, t_all *all, int start, int end)
{
	char		*str;
	int			j;

	if (end >= start)
	{
		while (line[start] == ' ') // убрали пробелы в начале строки
			start++;
		while (line[end] == ' ')
			end--;
		if (line[end] != ' ')
			end++;
		if (!(str = (char *)malloc(sizeof(char) * ((end + 1) - (start--))))) // почистить
			return (error_malloc());
		j = -1;
		while (++start < end)
			str[++j] = line[start];
		str[j + 1] = '\0';
		arguments_search(str, all);
		free(str);
	}
}