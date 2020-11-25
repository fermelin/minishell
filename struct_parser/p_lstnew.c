#include "../minishell.h"

t_data		*p_lstnew(void)
{
	t_data	*new_elem;

	new_elem = (t_data *)malloc(sizeof(t_data));
	if (!new_elem)
		return (NULL);
	new_elem->args = NULL;
	new_elem->file_name = NULL;
	new_elem->pipe = 0;
	new_elem->pipe_behind = 0;
	new_elem->red_to = 0;
	new_elem->red_from = 0;
	new_elem->doub_red_to = 0;
	new_elem->next = NULL;
	return (new_elem);
}
