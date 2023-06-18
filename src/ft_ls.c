/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:12:00 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/19 01:21:43 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ft_ls.h>

#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

static void	print_file_info(const char *filename)
{
	struct stat		file_stat;
	char			time_str[20];
	struct passwd	*pwd;
	struct group	*grp;

	if (stat(filename, &file_stat) < 0)
	{
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
	printf(" %s\n", filename);
}

static void	list_dir(const char *dirname, t_flags *flags)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dirname);
	if (dir == NULL)
	{
		perror("opendir");
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!flags->f_a && entry->d_name[0] == '.')
			continue ;
		print_file_info(entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
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
		return (-1);
	ls_loop(ls);
	return (0);
}
