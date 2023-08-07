/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utily.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:39:25 by cdarrell          #+#    #+#             */
/*   Updated: 2023/07/26 18:57:54 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdarg.h>
#include <errno.h>

void	ft_err_malloc(char *str)
{
	ft_putstr(str);
	exit (1);
}

void	ft_putstr_n(char *first_arg, ...)
{
	va_list	args;
	char	*arg;

	va_start(args, first_arg);
	arg = first_arg;
	while (*arg)
	{
		write(1, arg, ft_strlen(arg));
		arg = va_arg(args, char *);
	}
	va_end(args);
}

char	*path_to_file(char* dir_path, char* file_path)
{
	char	*new_path;
	char	*tmp;

	if (dir_path[0] == '\0')
		new_path = ft_strdup(file_path);
	else if (dir_path[ft_strlen(dir_path) - 1] == '/')
		new_path = ft_strjoin(dir_path, file_path);
	else
	{
		tmp = ft_strjoin(dir_path, "/");
		if (!tmp)
		{
			ft_putstr("Error malloc: utily.c - path_to_file - tmp\n");
			exit(-1);
		}
		new_path = ft_strjoin(tmp, file_path);
		free(tmp);
	}
	if (!new_path)
	{
		ft_putstr("Error malloc: utily.c - path_to_file - new_path\n");
		exit(-1);
	}
	return new_path;
}

bool	add_to_list(char *str_to_list, char *path, t_list **list)
{

	t_file_lstat *data = (t_file_lstat *)malloc(sizeof(t_file_lstat));
	if (!data)
	{
		ft_putstr("Error malloc: utily_lst.c - add_to_list - data\n");
		exit(-1);
	}

	data->full_path = path_to_file(path, str_to_list);
	if (lstat(data->full_path, &data->file_stat) != 0)
	{
		ft_putstr_n("ft_ls: cannot access '", data->full_path, "': ", strerror(errno), "\n", "\0");
		free(data->full_path);
		free(data);
		return false;
	}
	data->file_name = ft_strdup(str_to_list);
	if (!data->file_name)
	{
		ft_putstr("Error malloc: utily_lst.c - add_to_list - data->file_name\n");
		exit(-1);
	}

	t_list	*new_list;
	new_list = ft_lstnew(data);
	if (!new_list)
	{
		ft_putstr("Error malloc: utily_lst.c - add_to_list - new_list\n");
		exit(-1);
	}
	ft_lstadd_back(list, new_list);
	return true;
}

void	ft_lstclear_file_lstat(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		(*del)(((t_file_lstat*)(*lst)->content)->file_name);
		(*del)(((t_file_lstat*)(*lst)->content)->full_path);
		(*del)((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}
