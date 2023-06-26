/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:01:40 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/26 02:21:55 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

static void	print_file_info(const char *dirname, const char *content)
{
	struct stat		file_stat;
	char			time_str[20];
	struct passwd	*pwd;
	struct group	*grp;

	struct stat		file_stat2;
	stat(dirname, &file_stat2);
	char	*dirname2;
	if (S_ISDIR(file_stat.st_mode))
		dirname2 = ft_strjoin(dirname, "/");
	else
		dirname2 = ft_strjoin(".", "/");
	char	*filename = ft_strjoin(dirname2, content);
	printf("\t%s\n", filename);

	if (stat(filename, &file_stat) < 0)
	{
		if (!S_ISDIR(file_stat.st_mode))
			return
		perror("stat");
		return ;
	}
	// Вывод прав доступа к файлу
	printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
	printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
	printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
	printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
	printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
	printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
	printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
	printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
	printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
	printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
	// Вывод количества жестких ссылок
	printf(" %lu", file_stat.st_nlink);
	// Вывод информации о владельце и группе файла
	pwd = getpwuid(file_stat.st_uid);
	grp = getgrgid(file_stat.st_gid);
	printf(" %s %s", pwd->pw_name, grp->gr_name);
	// Вывод размера файла в байтах
	printf(" %ld", file_stat.st_size);
	// Вывод времени последней модификации файла
	strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
	printf(" %s", time_str);
	// Вывод имени файла
	printf(" %s\n", content);
}

static void	list_dir(const char *dirname, t_flags *flags)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*folder = NULL;

	struct stat		file_stat;
	stat(dirname, &file_stat);
	if (S_ISDIR(file_stat.st_mode))
	{
		dir = opendir(dirname);
		if (dir == NULL)
		{


			perror("opendir");
			return ;
		}
		while ((entry = readdir(dir)) != NULL)
		{
			if (!flags->f_a && entry->d_name[0] == '.')
				continue ;
			// print_file_info(entry->d_name);
			
			char	*tmp = ft_strdup(entry->d_name);
			if (!tmp)
				ft_err_malloc("Error malloc: parse.c - add_to_list - tmp");
			t_list	*new_list = ft_lstnew(tmp);
			if (!new_list)
				ft_err_malloc("Error malloc: parse.c - add_to_list - new_list");
			ft_lstadd_back(&folder, new_list);
		}
		closedir(dir);
	}
	else
	{
		char	*tmp = ft_strdup(dirname);
		if (!tmp)
			ft_err_malloc("Error malloc: parse.c - add_to_list - tmp");
		t_list	*new_list = ft_lstnew(tmp);
		if (!new_list)
			ft_err_malloc("Error malloc: parse.c - add_to_list - new_list");
		ft_lstadd_back(&folder, new_list);
	}

	
	t_list	*tmp_list = folder;
	while (tmp_list)
	{
		print_file_info(dirname, (char *)tmp_list->content);
		tmp_list = tmp_list->next;
	}

	if (flags->f_big_r)
	{
		printf("\n");
		tmp_list = folder;
		while (tmp_list)
		{
			// printf("11111\n");
			char *new_dir_r = ft_strjoin(dirname, "/");
			char *new_dir_r2 = ft_strjoin(new_dir_r, (char *)tmp_list->content);
			// printf("22222\n");	
			list_dir(new_dir_r2, flags);
			// printf("33333\n");
			tmp_list = tmp_list->next;
		}
	}
	return ;
}

static void	separate_dir_file_list(t_list *path, t_list **dir, t_list **file)
{
	struct stat		file_stat;

	*dir = NULL;
	*file = NULL;
	while (path)
	{
		if (stat((char *)path->content, &file_stat) == 0)
		{
			if (S_ISDIR(file_stat.st_mode))
				add_elem_to_list((char *)path->content, file_stat.st_mtime, dir);
			else
				add_elem_to_list((char *)path->content, file_stat.st_mtime, file);
		}
		else
		{
			ft_putstr_n("ft_ls: cannot access '", path->content, "': ", "\0");
			perror("");
		}
		path = path->next;
	}
}

static void separate_dir_file_list_print(t_list *file, t_list *dir)
{
	ft_putstr("====================================\n");
	ft_putstr("dir_file_list_print\n");
	ft_putstr("file:");
	while (file)
	{
		ft_putstr("\n\t");
		ft_putstr(((t_elem *)file->content)->name);
		file = file->next;
	}
	ft_putstr("\ndir:");
	while (dir)
	{
		ft_putstr("\n\t");
		ft_putstr(((t_elem *)dir->content)->name);
		dir = dir->next;
	}
	ft_putstr("\n");
	ft_putstr("====================================\n");
}

void	ls_loop(t_ls *ls)
{
	t_list			*dir;
	t_list			*file;

	separate_dir_file_list(ls->ls_path, &dir, &file);
	if (IS_DEBUG)
		separate_dir_file_list_print(file, dir);
	if (file)
	{
		ls_sort(&file, &ls->flags);
		ls_print(file, &ls->flags);
		if (dir)
			ft_putstr("\n");
	}

	// print_lst(dir, &ls->flags);
	// path = ls->ls_path;
	// while (path)
	// {
	// 	list_dir((char *)path->content, &ls->flags);
	// 	path = path->next;
	// }
	ft_lstclear_elem(&file);
	ft_lstclear_elem(&dir);
}
