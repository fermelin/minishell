/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_lists.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fermelin <fermelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 06:53:17 by fermelin          #+#    #+#             */
/*   Updated: 2020/11/24 13:35:44 by fermelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*p_lstnew(void)
{
	t_data	*newelem;

	if (!(newelem = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	newelem->args = NULL;
	newelem->file_name = NULL;
	newelem->pipe = 0;
	newelem->red_to = 0;
	newelem->doub_red_to = 0;
	newelem->red_from = 0;
	newelem->next = NULL;
	return (newelem);
}

void	p_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*tmp;

	if (!lst || !new)
		return ;
	tmp = (*lst);
	if (!(*lst))
		(*lst) = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	p_lstadd_front(t_data **lst, t_data *new)
{
	t_data *tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
		(*lst) = new;
	else
	{
		tmp = (*lst);
		(*lst) = new;
		new->next = tmp;
	}
}

void	p_lstclear(t_data **lst)
{
	t_data *tmp;

	if (!lst)
		return ;
	while ((*lst))
	{
		tmp = (*lst)->next;
		free_ptrs_array((*lst)->args);
		free((*lst)->file_name);
		(*lst) = tmp;
		free(*lst);
	}
	lst = NULL;
}

void	p_lstdelone(t_data *lst)
{
	if (lst)
	{
		free_ptrs_array(lst->args);
		free(lst->file_name);
	}
	free(lst);
}

// void	p_lstiter(t_data *lst, void (*f)(void *))
// {
// 	if (!lst || !f)
// 		return ;
// 	while (lst)
// 	{
// 		(*f)(lst->content);
// 		lst = lst->next;
// 	}
// }

t_data	*p_lstlast(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// t_data	*p_lstmap(t_data *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_data	*newlst;
// 	t_data	*beginning;

// 	if (!lst || !f || !(newlst = p_lstnew((*f)(lst->content))))
// 		return (NULL);
// 	beginning = newlst;
// 	while (lst->next)
// 	{
// 		lst = lst->next;
// 		if (lst && !(newlst->next = p_lstnew((*f)(lst->content))))
// 		{
// 			p_lstclear(&beginning, del);
// 			return (NULL);
// 		}
// 		newlst = newlst->next;
// 	}
// 	return (beginning);
// }

int		p_lstsize(t_data *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
