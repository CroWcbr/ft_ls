/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:31:10 by cdarrell          #+#    #+#             */
/*   Updated: 2023/08/10 23:03:42 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <stdio.h>

static int find_color(struct stat *file_stat)
{
	if (S_ISDIR(file_stat->st_mode))
		return 1;
	else if (S_ISLNK(file_stat->st_mode))
		return 2;
	else if (file_stat->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		return 3;
	else
		return 0;
}

static void set_color(bool color, int code)
{
	if (!color)
		return;
	
	if (code == 1)
		ft_putstr(BLUE);
	else if (code == 2)
		ft_putstr(PURPLE);
	else if (code == 3)
		ft_putstr(GREEN);
	else
		ft_putstr(WHITE);
}

static void	create_data_l(t_file_lstat *content, char **data, int* data_len, int *data_color, t_flags *flags, int *total)
{
	int				tmp_len;
	int				i;

	// index
	i = -1;
	if (flags->f_i)
	{
		data[++i] = ft_itoa(content->file_stat.st_ino);
		tmp_len = ft_strlen(data[i]);
		if (data_len[i] < tmp_len)
			data_len[i] = tmp_len;
	}

	// block size
	if (flags->f_s)
	{
		data[++i] = ft_itoa(content->file_stat.st_blocks);
		tmp_len = ft_strlen(data[i]);
		if (data_len[i] < tmp_len)
			data_len[i] = tmp_len;
	}
	*total += content->file_stat.st_blocks;

	// chmod
	data[++i] = (char*)malloc(11);
	data[i][0] = ((S_ISDIR(content->file_stat.st_mode)) ? 'd' : (S_ISLNK(content->file_stat.st_mode) ? 'l' : '-'));
	data[i][1] = ((content->file_stat.st_mode & S_IRUSR) ? 'r' : '-');
	data[i][2] = ((content->file_stat.st_mode & S_IWUSR) ? 'w' : '-');
	data[i][3] = ((content->file_stat.st_mode & S_IXUSR) ? 'x' : '-');
	data[i][4] = ((content->file_stat.st_mode & S_IRGRP) ? 'r' : '-');
	data[i][5] = ((content->file_stat.st_mode & S_IWGRP) ? 'w' : '-');
	data[i][6] = ((content->file_stat.st_mode & S_IXGRP) ? 'x' : '-');
	data[i][7] = ((content->file_stat.st_mode & S_IROTH) ? 'r' : '-');
	data[i][8] = ((content->file_stat.st_mode & S_IWOTH) ? 'w' : '-');
	data[i][9] = ((content->file_stat.st_mode & S_IXOTH) ? 'x' : '-');
	data[i][10] = '\0';
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	// hard link
	data[++i] = ft_itoa(content->file_stat.st_nlink);
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	// user
	if (!flags->f_g)
	{
		struct passwd* user_info;
		if (flags->f_n || !(user_info = getpwuid(content->file_stat.st_uid)))
			data[++i] = ft_itoa(content->file_stat.st_uid);
		else
			data[++i] = ft_strdup(user_info->pw_name);
		tmp_len = ft_strlen(data[i]);
		if (data_len[i] < tmp_len)
			data_len[i] = tmp_len;
	}

	// group

	if (!flags->f_o)
	{
		struct group* group_info;
		if (flags->f_n || !(group_info = getgrgid(content->file_stat.st_gid)))
			data[++i] = ft_itoa(content->file_stat.st_gid);
		else
			data[++i] = ft_strdup(group_info->gr_name);
		tmp_len = ft_strlen(data[i]);
		if (data_len[i] < tmp_len)
			data_len[i] = tmp_len;
	}

	// size
	data[++i] = ft_itoa(content->file_stat.st_size);
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	// time
	char time_str[20];
	ft_strcpy(time_str, ctime(&content->file_stat.st_mtime));
	time_str[16] = '\0';
	data[++i] = ft_strdup(time_str + 4);
	// strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&content->file_stat.st_mtime));
	// data[++i] = ft_strdup(time_str);
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	// file + link
	char *tmp = ft_strdup(content->file_name);
	if (S_ISLNK(content->file_stat.st_mode))
	{
		char *tmp2 = ft_strjoin(tmp, " -> ");
		free(tmp);
		char target[256];
		ssize_t len = readlink(content->full_path, target, sizeof(target) - 1);
		target[len] = '\0';
		tmp = ft_strjoin(tmp2, target);
		free(tmp2);
	}
	data[++i] = tmp;
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	*data_color = find_color(&content->file_stat);
}

static void	print_flag_l(t_list *lst, t_flags *flags)
{
	int	size = 7;
	if (flags->f_g)
		--size;
	if (flags->f_o)
		--size;
	if (flags->f_i)
		++size;
	if (flags->f_s)
		++size;

	char*	data[ft_lstsize(lst) + 1][size];
	int		data_color[ft_lstsize(lst)]; // 1 - dir, 2 - link, 3 - file
	int		total = 0;
	int		data_len[size];
	ft_memset(data_len, 0, sizeof(data_len));

	int	i = 0;
	while(lst)
	{
		create_data_l((t_file_lstat *)lst->content, data[i], data_len, &data_color[i], flags, &total);
		i++;
		lst = lst->next;
	}
	data[i][0] = NULL;

	if (!flags->print_file)
	{
		ft_putstr("total ");
		ft_putnbr_fd(total, 1);
		ft_putstr("\n");
	}
	for(int ii = 0; ii < i; ++ii)
	{
		int j;
		for(j = 0; j < size - 1; ++j)
		{
			int padding = data_len[j] - ft_strlen(data[ii][j]);
			while (padding > 0)
			{
				write(1, " ", 1);
				padding--;
			}
			ft_putstr(data[ii][j]);
			ft_putstr(" ");
			free(data[ii][j]);
		}
		set_color(flags->f_color, data_color[ii]);
		ft_putstr(data[ii][j]);
		ft_putstr(WHITE);
		ft_putstr("\n");
		free(data[ii][j]);
	}
}

static void	print_flag_m(t_list *lst, t_flags *flags)
{
	int total = 0;

	if (flags->f_s && !flags->print_file)
	{
		t_list *tmp = lst;
		while(tmp)
		{
			total += ((t_file_lstat*)tmp->content)->file_stat.st_blocks;
			tmp = tmp->next;
		}
		ft_putstr("total ");
		ft_putnbr_fd(total, 1);
		ft_putstr("\n");
	}
	while(lst)
	{
		if (flags->f_i)
		{
			ft_putnbr_fd(((t_file_lstat*)lst->content)->file_stat.st_ino, 1);
			ft_putstr(" ");
		}
		if (flags->f_s)
		{
			ft_putnbr_fd(((t_file_lstat*)lst->content)->file_stat.st_blocks, 1);
			ft_putstr(" ");
		}
		set_color(flags->f_color, find_color(&((t_file_lstat*)lst->content)->file_stat));
		ft_putstr(((t_file_lstat*)lst->content)->file_name);
		ft_putstr(WHITE);
		lst = lst->next;
		if (lst)
			ft_putstr(", ");
	}
	ft_putstr("\n");
}

static void	create_data_standart(t_file_lstat *content, char **data, int* data_len, int *data_color, t_flags *flags, int *total)
{
	int				tmp_len;
	int				i;

	i = -1;
	
	// index
	i = -1;
	if (flags->f_i)
	{
		data[++i] = ft_itoa(content->file_stat.st_ino);
		tmp_len = ft_strlen(data[i]);
		if (data_len[i] < tmp_len)
			data_len[i] = tmp_len;
	}

	// block size
	if (flags->f_s)
	{
		data[++i] = ft_itoa(content->file_stat.st_blocks);
		tmp_len = ft_strlen(data[i]);
		if (data_len[i] < tmp_len)
			data_len[i] = tmp_len;
	}
	*total += content->file_stat.st_blocks;

	// file + link
	data[++i] = ft_strdup(content->file_name);
	tmp_len = ft_strlen(data[i]);
	if (data_len[i] < tmp_len)
		data_len[i] = tmp_len;

	*data_color = find_color(&content->file_stat);
}

static void print_standart_table(t_list *lst, t_flags *flags)
{
	int	size = 1;
	if (flags->f_i)
		++size;
	if (flags->f_s)
		++size;

	int		lst_size = ft_lstsize(lst);
	char*	data[lst_size + 1][size];
	int		data_color[ft_lstsize(lst)]; // 1 - dir, 2 - link, 3 - file
	int		total = 0;
	int		data_len[size];
	ft_memset(data_len, 0, sizeof(data_len));

	int	i = 0;
	while(lst)
	{
		create_data_standart((t_file_lstat *)lst->content, data[i], data_len, &data_color[i], flags, &total);
		i++;
		lst = lst->next;
	}
	data[i][0] = NULL;

	struct	winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int		screen = w.ws_col;
	int		max_column_width = size;
	for (int i = 0; i < size; ++i)
		max_column_width += data_len[i];
	int		num_columns = screen / (max_column_width + 2);

	if (flags->f_s && !flags->print_file)
	{
		ft_putstr("total ");
		ft_putnbr_fd(total, 1);
		ft_putstr("\n");
	}

	for (int i = 0; i < lst_size; i++)
	{
		int j = 0;
		for (; j < size - 1; ++j)
		{
			int padding = data_len[j] - ft_strlen(data[i][j]);
			while (padding > 0)
			{
				write(1, " ", 1);
				padding--;
			}
			ft_putstr(data[i][j]);
			ft_putstr(" ");
			free(data[i][j]);
		}
		set_color(flags->f_color, data_color[i]);
		ft_putstr(data[i][j]);
		ft_putstr(WHITE);
		int padding = data_len[j] - ft_strlen(data[i][j]);
		free(data[i][j]);
		while (padding > 0)
		{
			write(1, " ", 1);
			padding--;
		}
		if ((i + 1) % num_columns == 0)
		{
			ft_putstr("\n");
		} else
		{
			ft_putstr("  ");
		}
	}
	ft_putstr("\n");
}

void	ls_print(t_list *lst, t_flags *flags, char *path)
{
	if (flags->print_endl)
		ft_putstr("\n");
	if (flags->print_dir)
	{
		ft_putstr_n(path, ":", "\0");
		if (lst)
			ft_putstr("\n");
	}

	if (flags->f_m)
	{
		print_flag_m(lst, flags);
	}
	else if (flags->f_l)
	{
		print_flag_l(lst, flags);
	}
	else 
	{
		print_standart_table(lst, flags);
	}
	flags->print_endl = true;
}
