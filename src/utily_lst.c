/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utily_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 23:19:20 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/28 23:40:08 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>

void	add_char_to_list(char *str_to_list, t_list **list)
{
	char	*tmp;
	t_list	*new_list;

	tmp = ft_strdup(str_to_list);
	if (!tmp)
	{
		ft_putstr("Error malloc: utily_lst.c - add_to_list - tmp\n");
		exit(-1);
	}
	new_list = ft_lstnew(tmp);
	if (!new_list)
	{
		ft_putstr("Error malloc: utily_lst.c - add_to_list - new_list\n");
		exit(-1);
	}
	ft_lstadd_back(list, new_list);
}

void	add_elem_to_list(char *name, time_t modified_time, t_list **list)
{
	t_list	*new_list;
	t_elem	*new_elem;

	new_elem = malloc(sizeof(t_elem));
	if (!new_elem)
		ft_err_malloc("Error malloc: utily_lst.c - add_elem_to_list - new_elem");
	new_elem->name = ft_strdup(name);
	if (!new_elem->name)
	{
		ft_putstr("Error malloc: utily_lst.c - add_elem_to_list - tmp\n");
		exit(-1);
	};
	new_elem->modified_time = modified_time;
	new_list = ft_lstnew(new_elem);
	if (!new_list)
	{
		ft_putstr("Error malloc: utily_lst.c - add_elem_to_list - new_list\n");
		exit(-1);
	}
	ft_lstadd_back(list, new_list);
}

void	ft_lstclear_elem(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(((t_elem*)((*lst)->content))->name);
		free((t_elem*)((*lst)->content));
		free(*lst);
		*lst = tmp;
	}
}
