#include "libft.h"
#include "minishell.h"

void			syntax_check(t_all *all, char *str, int **arr, t_list **new)
{
	int			i;
	char		*word;
	t_list		*temp;

	i = -1;
	temp = *new;
	if (!(word = ft_calloc(((*arr)[1] + 1) - (*arr)[0], sizeof(char))))
		return (error_malloc());
	search_variable(all, &word, str, arr);
	if (temp->content == NULL)
		temp->content = word;
	else
		ft_lstadd_back(&temp, ft_lstnew(word));
}

void			arguments_search(char *str, t_all *all)
{
	int			*arr;
	int			quotes[2];
	t_list		*new;

	new = NULL;
	arr = malloc(sizeof(int) * 2);
	arr[0] = 0;
	arr[1] = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	new = ft_lstnew(NULL);
	while (str[++arr[1]])
	{
		if (str[arr[1]] == '\'')
			quotes[0] = counting_quotes(str, quotes[0], quotes[1], arr[1]);
		else if (str[arr[1]] == '\"')
			quotes[1] = counting_quotes(str, quotes[0], quotes[1], arr[1]);
		else if (str[arr[1]] == ' ' && quotes[0] % 2 == 0 && quotes[1] % 2 == 0)
		{
			syntax_check(all, str, &arr, &new);
			while (str[arr[1]++] == ' ')
				arr[0] = arr[1];
			arr[1] = arr[0] - 1;
		}
	}
	syntax_check(all, str, &arr, &new);
	filling_struct(all, new, ft_lstsize(new));
	ft_lstclear(&new, NULL);
	free(arr);
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
