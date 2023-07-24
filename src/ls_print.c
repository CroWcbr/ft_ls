/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:31:10 by cdarrell          #+#    #+#             */
/*   Updated: 2023/07/24 02:26:08 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>

static void	create_data_l(char *dirname, char *content, char **data, int* data_len)
{
	char			*file_path;
	int				tmp_len;
	struct stat		file_stat;
	int				i;

	file_path = path_to_file(dirname, content);
	lstat(file_path, &file_stat);
	i = -1;

	// Вывод прав доступа к файлу
	char d1[11];
	d1[0] = ((S_ISDIR(file_stat.st_mode)) ? 'd' : (S_ISLNK(file_stat.st_mode) ? 'l' : '-'));
	d1[1] = ((file_stat.st_mode & S_IRUSR) ? 'r' : '-');
	d1[2] = ((file_stat.st_mode & S_IWUSR) ? 'w' : '-');
	d1[3] = ((file_stat.st_mode & S_IXUSR) ? 'x' : '-');
	d1[4] = ((file_stat.st_mode & S_IRGRP) ? 'r' : '-');
	d1[5] = ((file_stat.st_mode & S_IWGRP) ? 'w' : '-');
	d1[6] = ((file_stat.st_mode & S_IXGRP) ? 'x' : '-');
	d1[7] = ((file_stat.st_mode & S_IROTH) ? 'r' : '-');
	d1[8] = ((file_stat.st_mode & S_IWOTH) ? 'w' : '-');
	d1[9] = ((file_stat.st_mode & S_IXOTH) ? 'x' : '-');
	d1[10] = '\0';
	data[++i] = ft_strdup(d1);
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	// Вывод количества жестких ссылок
	data[++i] = ft_itoa(file_stat.st_nlink);
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	// Вывод информации о владельце и группе файла
	data[++i] = ft_strdup(getpwuid(file_stat.st_uid)->pw_name);
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;
	data[++i] = ft_strdup(getgrgid(file_stat.st_gid)->gr_name);
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	// Вывод размера файла в байтах
	data[++i] = ft_itoa(file_stat.st_size);
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	// Вывод времени последней модификации файла
	char time_str[20];
	strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
	data[++i] = ft_strdup(time_str);
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	char *tmp = ft_strdup(content);
	if (S_ISLNK(file_stat.st_mode))
	{
		char *tmp2 = ft_strjoin(tmp, " -> ");
		free(tmp);
		char target[256];
		ssize_t len = readlink(file_path, target, sizeof(target) - 1);
		target[len] = '\0';
		tmp = ft_strjoin(tmp2, target);
		free(tmp2);
	}
	data[++i] = tmp;
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	free(file_path);
}

static void	print_file_info(char *dirname, char *content)
{
	struct stat		file_stat;
	// char			time_str[20];
	// struct passwd	*pwd;
	// struct group	*grp;

	// struct stat		file_stat2;
	// stat(dirname, &file_stat2);
	// char	*dirname_tmp;
	// char	*dirname_tmp2;
	// if (content[0] == '.' && content[1] == '/')
	// {
	// 	dirname_tmp2 = ft_strdup(content);
	// }
	// else
	// {
	// 	if (dirname[ft_strlen(dirname) - 1] != '/')
	// 	{
	// 		dirname_tmp = ft_strjoin(dirname, "/");
	// 	}
	// 	else
	// 		dirname_tmp = ft_strdup(dirname);
	// 	dirname_tmp2 = ft_strjoin(dirname_tmp, content);
	// }

	char	*dirname_tmp2 = path_to_file(dirname, content);

	lstat(dirname_tmp2, &file_stat);
	// if (S_ISDIR(file_stat.st_mode))
	// 	dirname2 = ft_strjoin(dirname, "/");
	// else
	// 	dirname2 = ft_strjoin(".", "/");
	// char	*filename = ft_strjoin(dirname2, content);
	// printf("\t%s\n", filename);

	// if (stat(filename, &file_stat) < 0)
	// {
	// 	if (!S_ISDIR(file_stat.st_mode))
	// 		return
	// 	perror("stat");
	// 	return ;
	// }
	// ft_putstr(dirname_tmp2);
	// ft_putstr("\t");

	// Вывод прав доступа к файлу// Вывод количества жестких ссылок
	ft_putstr((S_ISDIR(file_stat.st_mode)) ? "d" : (S_ISLNK(file_stat.st_mode) ? "l" : "-"));
	ft_putstr((file_stat.st_mode & S_IRUSR) ? "r" : "-");
	ft_putstr((file_stat.st_mode & S_IWUSR) ? "w" : "-");
	ft_putstr((file_stat.st_mode & S_IXUSR) ? "x" : "-");
	ft_putstr((file_stat.st_mode & S_IRGRP) ? "r" : "-");
	ft_putstr((file_stat.st_mode & S_IWGRP) ? "w" : "-");
	ft_putstr((file_stat.st_mode & S_IXGRP) ? "x" : "-");
	ft_putstr((file_stat.st_mode & S_IROTH) ? "r" : "-");
	ft_putstr((file_stat.st_mode & S_IWOTH) ? "w" : "-");
	ft_putstr((file_stat.st_mode & S_IXOTH) ? "x" : "-");
	// Вывод количества жестких ссылок
	ft_putstr(" ");
	ft_putnbr_fd(file_stat.st_nlink, 1);
	// Вывод информации о владельце и группе файла
	ft_putstr(" ");
	ft_putstr(getpwuid(file_stat.st_uid)->pw_name);
	ft_putstr(" ");
	ft_putstr(getgrgid(file_stat.st_gid)->gr_name);
	ft_putstr(" ");
	// printf(" %s %s", pwd->pw_name, grp->gr_name);
	// Вывод размера файла в байтах
	ft_putnbr_fd(file_stat.st_size, 1);
	// printf(" %ld", file_stat.st_size);
	// Вывод времени последней модификации файла
	char time_str[20];
	strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
	ft_putstr(" ");
	ft_putstr(time_str);
	ft_putstr(" ");
	// printf(" %s", time_str);
	// // Вывод имени файла
	// printf(" %s\n", content);

ft_putstr(content);

if (S_ISLNK(file_stat.st_mode))
{
	char target[256]; // Задайте достаточно большой буфер для хранения содержимого ссылки
	ssize_t len = readlink(dirname_tmp2, target, sizeof(target) - 1);


	ft_putstr(" -> ");
	write(1, target, len);
	// ft_putstr(strrchr(target, '/'));
}


	ft_putstr(" ");
}

void	ls_print(t_list *lst, t_flags *flags, char *path)
{
	if (flags->print_endl)
		ft_putstr("\n");
	if (flags->print_dir)
		ft_putstr_n(path, ":\n", "\0");
	t_list *tmp = lst;

	int	i = 0;
	if (flags->f_l)
	{
		char*	data[ft_lstsize(lst) + 1][7];
		int		data_len[7] = {0};
		while(lst)
		{
			create_data_l(path, (char *)lst->content, data[i++], data_len);
			lst = lst->next;
		}
		data[i][0] = NULL;

		for(int ii = 0; ii < i; ++ii)
		{
			int j;
			for(j = 0; j < 6; ++j)
			{
				int padding = data_len[j] - ft_strlen(data[ii][j]);
				while (padding > 0)
				{
					write(1, " ", 1);
					padding--;
				}
				ft_putstr(data[ii][j]);
				ft_putstr(" ");
			}
			ft_putstr(data[ii][j]);
			ft_putstr("\n");
		}
	}
	// lst = tmp;
	// while(lst)
	// {
	// 	if (flags->f_l)
	// 	{
	// 		print_file_info(path, (char *)lst->content);
	// 		ft_putstr("\n");
	// 	}
	// 	else
	// 	{
	// 		ft_putstr((char *)lst->content);
	// 		ft_putstr("\n");
	// 	}

	// 	lst = lst->next;
	// }
	flags->print_endl = true;
}
