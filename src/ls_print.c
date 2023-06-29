/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:31:10 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/29 02:23:01 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

void	ls_print(t_list *lst, t_flags *flags, char *path)
{
	while(lst)
	{
		ft_putstr((char *)lst->content);
		ft_putstr("\n");
		lst = lst->next;
	}
}

// static void	print_file_info(const char *dirname, const char *content)
// {
// 	struct stat		file_stat;
// 	char			time_str[20];
// 	struct passwd	*pwd;
// 	struct group	*grp;

// 	struct stat		file_stat2;
// 	stat(dirname, &file_stat2);
// 	char	*dirname2;
// 	if (S_ISDIR(file_stat.st_mode))
// 		dirname2 = ft_strjoin(dirname, "/");
// 	else
// 		dirname2 = ft_strjoin(".", "/");
// 	char	*filename = ft_strjoin(dirname2, content);
// 	printf("\t%s\n", filename);

// 	if (stat(filename, &file_stat) < 0)
// 	{
// 		if (!S_ISDIR(file_stat.st_mode))
// 			return
// 		perror("stat");
// 		return ;
// 	}
// 	// Вывод прав доступа к файлу
// 	printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
// 	printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
// 	printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
// 	printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
// 	printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
// 	printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
// 	printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
// 	printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
// 	printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
// 	printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
// 	// Вывод количества жестких ссылок
// 	printf(" %lu", file_stat.st_nlink);
// 	// Вывод информации о владельце и группе файла
// 	pwd = getpwuid(file_stat.st_uid);
// 	grp = getgrgid(file_stat.st_gid);
// 	printf(" %s %s", pwd->pw_name, grp->gr_name);
// 	// Вывод размера файла в байтах
// 	printf(" %ld", file_stat.st_size);
// 	// Вывод времени последней модификации файла
// 	strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
// 	printf(" %s", time_str);
// 	// Вывод имени файла
// 	printf(" %s\n", content);
// }