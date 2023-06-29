/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:01:40 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/29 02:52:34 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

static void	dir_loop(char* dir_path, t_flags* flags);

static void	dir_loop_flag_r(t_list *dir, t_flags* flags, char *path)
{
	struct	stat	file_stat;
	char			*final_path;

	while(dir)
	{
		final_path = path_to_file(path, (char*)dir->content);
		if (stat(final_path, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
				dir_loop(final_path, flags);
		}
		else
		{
			ft_putstr_n("ft_ls: cannot access '", final_path, "': ", strerror(errno), "\n", "\0");
		}
		free(final_path);
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
		if (entry->d_name[0] == '.' && !flags->f_a)
			continue ;
		add_char_to_list(entry->d_name, &this_dir_list);
	}
	ls_sort(&this_dir_list, flags, dir_path);
	ls_print(this_dir_list, flags, dir_path);
	if (flags->f_big_r)
		dir_loop_flag_r(this_dir_list, flags, dir_path);
	ft_lstclear(&this_dir_list, free);
	closedir(dir);
}

static void	separate_dir_file_list(t_list *path, t_list **dir, t_list **file)
{
	struct stat	file_stat;

	*dir = NULL;
	*file = NULL;
	while (path)
	{
		if (stat((char *)path->content, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
				add_char_to_list((char *)path->content, dir);
			else
				add_char_to_list((char *)path->content, file);
		}
		else
		{
			ft_putstr_n("ft_ls: cannot access '", path->content, "': ", strerror(errno), "\n", "\0");
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
		ft_putstr((char *)file->content);
		file = file->next;
	}
	ft_putstr("\ndir:");
	while (dir)
	{
		ft_putstr("\n\t");
		ft_putstr((char *)dir->content);
		dir = dir->next;
	}
	ft_putstr("\n");
	ft_putstr("====================================\n");
}

void	ls_loop(t_ls *ls)
{
	t_list			*dir;
	t_list			*file;
	t_list			*tmp_dir;

	separate_dir_file_list(ls->ls_path, &dir, &file);
	if (IS_DEBUG)
		separate_dir_file_list_print(file, dir);
	if (file)
	{
		ls_sort(&file, &ls->flags, "");
		ls_print(file, &ls->flags, "");
	}

	if (dir)
	{
		ls_sort(&dir, &ls->flags, "");
		tmp_dir = dir;
		while (tmp_dir)
		{
			if (file)
			{
				ft_putstr("\n");
				if (!ls->flags.f_big_r)
					ft_putstr_n((char*)tmp_dir->content, ":\n", "\0");
			}
			dir_loop((char*)tmp_dir->content, &ls->flags);
			tmp_dir = tmp_dir->next;
		}
	}
	ft_lstclear(&file, free);
	ft_lstclear(&dir, free);
}
