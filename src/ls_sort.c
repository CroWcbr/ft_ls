/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:31:08 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/28 20:18:31 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>

static bool	noflag_compare(t_elem* elem1, t_elem* elem2)
{
	char* str1 = elem1->name;
	char* str2 = elem2->name;

	for(size_t i = 0; ft_strlen(str1); ++i)
	{
		if (str1[i] == str2[i])
			continue;
		if (str2[i] > str1[i])
			return true;
		else
			return false;
	}
	return true;
}

static bool	t_flag_compare(t_elem* elem1, t_elem* elem2)
{
	return (elem1->modified_time >= elem2->modified_time);
}

static void	split_list(t_list* head, t_list** leftHalf, t_list** rightHalf)
{
	t_list* slow;
	t_list* fast;

	slow = head;
	fast = head;
	while (fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	*leftHalf = head;
	*rightHalf = slow->next;
	slow->next = NULL;
}

static t_list*	merge_lists(t_list* left, t_list* right, bool (*flag_compare)(t_elem*, t_elem*))
{
	t_list* result;
	
	result = NULL;
	if (left == NULL)
		return right;
	if (right == NULL)
		return left;
	if (flag_compare((t_elem*)left->content, (t_elem*)right->content))
	{
		result = left;
		result->next = merge_lists(left->next, right, flag_compare);
	}
	else
	{
		result = right;
		result->next = merge_lists(left, right->next, flag_compare);
	}
	return result;
}

static void	sort_list(t_list** head, bool (*flag_compare)(t_elem*, t_elem*))
{
	t_list*	current;
	t_list*	leftHalf;
	t_list*	rightHalf;

	current =  *head;
	if (current == NULL || current->next == NULL)
		return;
	split_list(current, &leftHalf, &rightHalf);
	sort_list(&leftHalf, flag_compare);
	sort_list(&rightHalf, flag_compare);
	*head = merge_lists(leftHalf, rightHalf, flag_compare);
}

static void	reverse_list(t_list** head)
{
	t_list*	prev;
	t_list*	current;
	t_list*	next;

	prev = NULL;
	current = *head;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}

void	ls_sort(t_list** lst, t_flags* flags)
{
	if (flags->f_t)
		sort_list(lst, t_flag_compare);
	else if (flags->f_f)
		;
	else
		sort_list(lst, noflag_compare);
	if (flags->f_r)
		reverse_list(lst);
}
