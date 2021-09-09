
#include "minishell.h"

void	initial_params(t_all *all, int **start)
{
	all->params.arr[0] = (*start)[0];
	all->params.arr[1] = (*start)[1];
	all->params.quotes[0] = 0;
	all->params.quotes[1] = 0;
	all->params.i = 0;
}

void	dash(t_all *all, char **word, char *str, int **start)
{
	if (!(all->params.quotes[0] % 2) && !(all->params.quotes[1] % 2))
		(*word)[all->params.i] = str[++(*start)[0]];
	else if (all->params.quotes[0] % 2 && !(all->params.quotes[1] % 2))
		(*word)[all->params.i] = str[(*start)[0]];
	else if (!(all->params.quotes[0] % 2) && all->params.quotes[1] % 2)
	{
		if (str[(*start)[0] + 1] == '$' || str[(*start)[0] + 1] == '\\' ||
			str[(*start)[0] + 1] == '\"')
			(*word)[all->params.i] = str[++(*start)[0]];
		else
			(*word)[all->params.i] = str[(*start)[0]];
	}
}

void	two_quotes(t_all *all, char **word, char *str, int **start)
{
	all->params.quotes[1]++;
	if (all->params.quotes[0] % 2)
	{
		(*word)[all->params.i] = str[(*start)[0]];
		all->params.quotes[1]++;
	}
	else if (!(all->params.quotes[0] % 2))
		all->params.i--;
}

void	one_quotes(t_all *all, char **word, char *str, int **start)
{
	all->params.quotes[0]++;
	if (all->params.quotes[1] % 2)
	{
		(*word)[all->params.i] = str[(*start)[0]];
		all->params.quotes[0]++;
	}
	else if (!(all->params.quotes[1] % 2))
		all->params.i--;
}
