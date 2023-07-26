/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:01:40 by cdarrell          #+#    #+#             */
/*   Updated: 2023/07/26 23:26:51 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <dirent.h>
#include <errno.h>

static void	dir_loop(char* dir_path, t_flags* flags);

static void	dir_loop_flag_r(t_list *dir, t_flags* flags)
{
	t_file_lstat	*tmp;
	while(dir)
	{
		tmp = (t_file_lstat*)dir->content;
		if (ft_strcmp(tmp->file_name, ".") && \
			ft_strcmp(tmp->file_name, ".."))
		{
			if (S_ISDIR(tmp->file_stat.st_mode))
			{
				dir_loop(tmp->full_path, flags);
			}
		}
		dir = dir->next;
	}
}

static void	dir_loop(char* dir_path, t_flags* flags)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*this_dir_list;

	this_dir_list = NULL;
	dir = opendir(dir_path);
	if (dir == NULL)
	{
		ft_putstr_n("ft_ls: cannot open directory '", dir_path, "': ", strerror(errno), "\n", "\0");
		return ;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (flags->f_a)
		{
			add_to_list(entry->d_name, dir_path, &this_dir_list);
		}
		else if (flags->f_A)
		{
			if (ft_strcmp(entry->d_name, "..") && ft_strcmp(entry->d_name, "."))
			{
				add_to_list(entry->d_name, dir_path, &this_dir_list);
			}
		}
		else if (entry->d_name[0] != '.')
		{
			add_to_list(entry->d_name, dir_path, &this_dir_list);
		}
	}
	closedir(dir);
	ls_sort(&this_dir_list, flags);
	ls_print(this_dir_list, flags, dir_path);
	if (flags->f_R)
		dir_loop_flag_r(this_dir_list, flags);
	ft_lstclear_file_lstat(&this_dir_list, free);
}

static void	separate_dir_file_list(t_list *path, t_list **dir, t_list **file)
{
	t_file_lstat*	tmp;
	while (path)
	{
		tmp = (t_file_lstat*)path->content;
		if (S_ISDIR(tmp->file_stat.st_mode))
		{
			add_to_list(tmp->file_name, "", dir);
		}
		else
		{
			add_to_list(tmp->file_name, "", file);
		}
		path = path->next;
	}
}

static void separate_dir_file_list_print(t_list *file, t_list *dir)
{
	ft_putstr("====================================\n");
	ft_putstr("dir_file_list_print :\n");
	ft_putstr("file:");
	while (file)
	{
		ft_putstr("\n\t");
		ft_putstr(((t_file_lstat *)file->content)->file_name);
		file = file->next;
	}
	ft_putstr("\ndir:");
	while (dir)
	{
		ft_putstr("\n\t");
		ft_putstr(((t_file_lstat *)dir->content)->file_name);
		dir = dir->next;
	}
	ft_putstr("\n");
	ft_putstr("====================================\n");
}

void	ls_loop(t_ls *ls)
{
	if (ls->flags.f_d)
	{
		ls_sort(&ls->ls_path, &ls->flags);
		ls_print(ls->ls_path, &ls->flags, "");
		return ;
	}

	t_list	*dir = NULL;
	t_list	*file = NULL;
	t_list	*tmp_dir = NULL;

	separate_dir_file_list(ls->ls_path, &dir, &file);
	if (IS_DEBUG)
		separate_dir_file_list_print(file, dir);
	if (file)
	{
		ls->flags.print_file = true;
		ls_sort(&file, &ls->flags);
		ls_print(file, &ls->flags, "");
		ls->flags.print_file = false;
	}
	if ((file && dir) || ft_lstsize(dir) > 1 || ls->flags.f_R)
	{
		ls->flags.print_dir = true;
	}
	if (dir)
	{
		ls_sort(&dir, &ls->flags);
		tmp_dir = dir;
		while (tmp_dir)
		{
			dir_loop(((t_file_lstat*)tmp_dir->content)->file_name, &ls->flags);
			tmp_dir = tmp_dir->next;
		}
	}
	ft_lstclear_file_lstat(&file, free);
	ft_lstclear_file_lstat(&dir, free);
}
