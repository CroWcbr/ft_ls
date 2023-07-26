/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:31:08 by cdarrell          #+#    #+#             */
/*   Updated: 2023/07/26 21:43:05 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>
#include <sys/stat.h>
#include <errno.h>

static bool	noflag_compare(t_file_lstat* file1, t_file_lstat* file2)
{
	for(size_t i = 0; i < ft_strlen(file1->file_name); ++i)
	{
		if (file1->file_name[i] == file2->file_name[i])
			continue;
		if (file2->file_name[i] > file1->file_name[i])
			return true;
		else
			return false;
	}
	return true;
}

static bool	t_flag_compare(t_file_lstat* file1, t_file_lstat* file2)
{
	if (file1->file_stat.st_mtime == file2->file_stat.st_mtime)
		return noflag_compare(file1, file2);
	return (file1->file_stat.st_mtime > file2->file_stat.st_mtime);
}

static bool	S_flag_compare(t_file_lstat* file1, t_file_lstat* file2)
{
	if (file1->file_stat.st_size == file2->file_stat.st_size)
		return noflag_compare(file1, file2);
	return (file1->file_stat.st_size > file2->file_stat.st_size);
}

t_list*	merge(t_list* left, t_list* right, bool (*compare_func)(t_file_lstat*, t_file_lstat*))
{
	t_list result;
	t_list* tail = &result;

	while (left && right)
	{
		if (compare_func((t_file_lstat*)left->content, (t_file_lstat*)right->content))
		{
			tail->next = left;
			left = left->next;
		} 
		else
		{
			tail->next = right;
			right = right->next;
		}
		tail = tail->next;
	}

	tail->next = (left != NULL) ? left : right;
	return result.next;
}

static void	sort_list(t_list** head, bool (*compare_func)(t_file_lstat*, t_file_lstat*))
{
	if (*head == NULL || (*head)->next == NULL)
	{
		return;
	}

	t_list* slow = *head;
	t_list* fast = (*head)->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	t_list	*left = *head;
	t_list	*right = slow->next;
	slow->next = NULL;

	sort_list(&left, compare_func);
	sort_list(&right, compare_func);

	*head = merge(left, right, compare_func);
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
	if (ft_lstsize(*lst) < 2)
		return ;
	if (flags->f_t)
		sort_list(lst, t_flag_compare);
	else if (flags->f_S)
		sort_list(lst, S_flag_compare);
	else if (flags->f_U)
		;
	else
		sort_list(lst, noflag_compare);
	if (flags->f_r)
		reverse_list(lst);
}
