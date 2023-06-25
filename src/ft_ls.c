/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:12:00 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/25 17:33:10 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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

static void	ls_loop(t_ls *ls)
{
	t_list	*path;

	path = ls->ls_path;
	while (path)
	{
		list_dir((char *)path->content, &ls->flags);
		path = path->next;
	}
}

int	main(int argc, char **argv)
{
	t_ls	*ls;

	(void)argc;
	ls = parse(++argv);
	if (!ls)
		return (1);
	ls_loop(ls);
	return (0);
}
