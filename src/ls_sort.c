/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:31:08 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/29 02:51:29 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>
#include <sys/stat.h>
#include <errno.h>

static bool	noflag_compare(char* str1, char* str2, char *path)
{
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

static bool	t_flag_compare(char* str1, char* str2, char *path)
{
	struct stat	file_stat1;
	struct stat	file_stat2;
	char		*file1 = path_to_file(path, str1);
	char		*file2 = path_to_file(path, str2);

	if (lstat(file1, &file_stat1))
	{
		ft_putstr_n("ft_ls: cannot access '", str1, "': ", strerror(errno), "\n", "\0");
		exit(-1);
	}
	if (lstat(file2, &file_stat2))
	{
		ft_putstr_n("ft_ls: cannot access '", str2, "': ", strerror(errno), "\n", "\0");
		exit(-1);
	}
	free(file1);
	free(file2);
	if (file_stat1.st_mtime == file_stat2.st_mtime)
		return noflag_compare(str1, str2, "");
	return (file_stat1.st_mtime > file_stat2.st_mtime);
}

t_list*	merge(t_list* left, t_list* right, char *path, \
					bool (*compare_func)(char*, char*, char*))
{
	t_list result;
	t_list* tail = &result;

	while (left && right)
	{
		if (compare_func((char*)left->content, (char*)right->content, path))
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

static void	sort_list(t_list** head, char *path, \
						bool (*compare_func)(char*, char*, char*))
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

	sort_list(&left, path, compare_func);
	sort_list(&right, path, compare_func);

	*head = merge(left, right, path, compare_func);
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

void	ls_sort(t_list** lst, t_flags* flags, char *path)
{
	if (ft_lstsize(*lst) < 2)
		return ;
	if (flags->f_t)
		sort_list(lst, path, t_flag_compare);
	else if (flags->f_f)
		;
	else
		sort_list(lst, path, noflag_compare);
	if (flags->f_r)
		reverse_list(lst);
}
