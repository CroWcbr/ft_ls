/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:00:13 by cdarrell          #+#    #+#             */
/*   Updated: 2023/08/10 22:47:49 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	parse_print(t_ls *ls)
{
	t_list	*tmp;

	ft_putstr("====================================\n");
	ft_putstr("parse_print : \n");
	ft_putstr("flag : \n");
	ft_putstr("\t\tl\t:\t");
	ft_putnbr_fd(ls->flags.f_l, 1);
	ft_putstr("\n\t\tR\t:\t");
	ft_putnbr_fd(ls->flags.f_R, 1);
	ft_putstr("\n\t\ta\t:\t");
	ft_putnbr_fd(ls->flags.f_a, 1);
	ft_putstr("\n\t\tr\t:\t");
	ft_putnbr_fd(ls->flags.f_r, 1);
	ft_putstr("\n\t\tt\t:\t");
	ft_putnbr_fd(ls->flags.f_t, 1);

	ft_putstr("\n\t\tcolor\t:\t");
	ft_putnbr_fd(ls->flags.f_color, 1);
	ft_putstr("\n\t\tA\t:\t");
	ft_putnbr_fd(ls->flags.f_A, 1);
	ft_putstr("\n\t\td\t:\t");
	ft_putnbr_fd(ls->flags.f_d, 1);
	ft_putstr("\n\t\tg\t:\t");
	ft_putnbr_fd(ls->flags.f_g, 1);
	ft_putstr("\n\t\ti\t:\t");
	ft_putnbr_fd(ls->flags.f_i, 1);
	ft_putstr("\n\t\tm\t:\t");
	ft_putnbr_fd(ls->flags.f_m, 1);
	ft_putstr("\n\t\tn\t:\t");
	ft_putnbr_fd(ls->flags.f_n, 1);
	ft_putstr("\n\t\to\t:\t");
	ft_putnbr_fd(ls->flags.f_o, 1);
	ft_putstr("\n\t\ts\t:\t");
	ft_putnbr_fd(ls->flags.f_s, 1);
	ft_putstr("\n\t\tS\t:\t");
	ft_putnbr_fd(ls->flags.f_S, 1);
	ft_putstr("\n\t\tU\t:\t");
	ft_putnbr_fd(ls->flags.f_U, 1);

	ft_putstr("\n\t\tprint_endl\t:\t");
	ft_putnbr_fd(ls->flags.print_endl, 1);
	ft_putstr("\n\t\tprint_dir\t:\t");
	ft_putnbr_fd(ls->flags.print_dir, 1);

	ft_putstr("\npath for ls :");
	tmp = ls->ls_path;
	while (tmp)
	{
		ft_putstr("\n\t\t");
		ft_putstr(((t_file_lstat *)tmp->content)->file_name);
		tmp = tmp->next;
	}
	ft_putstr("\n");
	ft_putstr("====================================\n");
}

static t_ls	*init(void)
{
	t_ls	*ls;

	ls = malloc(sizeof(t_ls));
	if (!ls)
		ft_err_malloc("Error malloc: parse.c - init - ls");
	ls->flags.f_l = false;
	ls->flags.f_R = false;
	ls->flags.f_a = false;
	ls->flags.f_r = false;
	ls->flags.f_t = false;

	ls->flags.f_color = false;
	ls->flags.f_A = false;
	ls->flags.f_d = false;
	ls->flags.f_g = false;
	ls->flags.f_i = false;
	ls->flags.f_m = false;
	ls->flags.f_n = false;
	ls->flags.f_o = false;
	ls->flags.f_s = false;
	ls->flags.f_S = false;
	ls->flags.f_U = false;

	ls->flags.print_file = false;
	ls->flags.print_endl = false;
	ls->flags.print_dir = false;
	ls->ls_path = NULL;
	return (ls);
}

static void	print_usage()
{
	ft_putstr_n
	(	
		"Usage: ls [OPTION]... [FILE]...\n", \
		"Mandatory arguments:\n", \
		"\t-a\tdo not ignore entries starting with .\n", \
		"\t-l\tuse a long listing format\n", \
		"\t-r\treverse order while sorting\n", \
		"\t-R\tlist subdirectories recursively\n", \
		"\t-t\tsort by modification time, newest first\n", \
		"Bonus arguments:\n", \
		"\t-A\tdo not list implied . and ..\n", \
		"\t-d\tlist directories themselves, not their contents\n", \
		"\t-f\tdo not sort, enable -aU, disable -ls --color\n", \
		"\t-g\tlike -l, but do not list owner\n", \
		"\t-i\tprint the index number of each file\n", \
		"\t-m\tfill width with a comma separated list of entries\n", \
		"\t-n\tlike -l, but list numeric user and group IDs\n", \
		"\t-o\tlike -l, but do not list group information\n", \
		"\t-s\tprint the allocated size of each file, in blocks\n", \
		"\t-S\tsort by file size, largest first\n", \
		"\t-U\tdo not sort; list entries in directory order\n", \
		"\t--help\tdisplay this help and exit\n", \
		"\t--color\tcolorize the output\n", \
		"\0"
	);
}

static void	clear_sort_flag(t_flags* flag)
{
	flag->f_S = false;
	flag->f_t = false;
	flag->f_U = false;
}

static bool	parse_flag(char *flags, t_ls *ls)
{
	while (*flags)
	{
		if (*flags == 'l')
			ls->flags.f_l = true;
		else if (*flags == 'R')
			ls->flags.f_R = true;
		else if (*flags == 'a')
		{
			ls->flags.f_a = true;
			ls->flags.f_A = false;
		}
		else if (*flags == 'r')
			ls->flags.f_r = true;
		else if (*flags == 't')
		{
			clear_sort_flag(&ls->flags);
			ls->flags.f_t = true;
		}
		else if (*flags == 'A')
		{
			ls->flags.f_A = true;
			ls->flags.f_a = false;
		}
		else if (*flags == 'd')
			ls->flags.f_d = true;

		else if (*flags == 'f')
		{
			clear_sort_flag(&ls->flags);
			ls->flags.f_U = true;
			ls->flags.f_a = true;
			ls->flags.f_A = false;
			ls->flags.f_s = false;
			ls->flags.f_l = false;
			ls->flags.f_color = false;
		}
		else if (*flags == 'g')
		{
			ls->flags.f_g = true;
			ls->flags.f_l = true;
		}
		else if (*flags == 'i')
			ls->flags.f_i = true;
		else if (*flags == 'm')
			ls->flags.f_m = true;
		else if (*flags == 'n')
			ls->flags.f_n = true;
		else if (*flags == 'o')
		{
			ls->flags.f_o = true;
			ls->flags.f_l = true;
		}
		else if (*flags == 's')
			ls->flags.f_s = true;
		else if (*flags == 'S')
		{
			clear_sort_flag(&ls->flags);
			ls->flags.f_S = true;
		}
		else if (*flags == 'U')
		{
			clear_sort_flag(&ls->flags);
			ls->flags.f_U = true;
		}
		else
		{
			ft_putstr_n("ft_ls: invalid option: ", flags, "\n", \
						"Try 'ls --help' for more information.\n","\0");
			return (false);
		}
		flags++;
	}
	return (true);
}

t_ls	*parse(char **argv)
{
	t_ls	*ls = NULL;
	bool	file = false;

	ls = init();
	while (*argv)
	{
		if ((*argv)[0] == '-' && (*argv)[1])
		{
			if (!ft_strcmp(*argv, "--color"))
			{
				ls->flags.f_color = true;
			}
			else if (!ft_strcmp(*argv, "--help"))
			{
				print_usage();
				ft_lstclear_file_lstat(&ls->ls_path, free);
				return (NULL);
			}
			else if ((*argv)[1] == '-')
			{
				ft_putstr_n("ft_ls: invalid option: ", *argv, "\n", \
						"Try 'ls --help' for more information.\n","\0");
				ft_lstclear_file_lstat(&ls->ls_path, free);
				return (NULL);
			}
			else if (!parse_flag(++(*argv), ls))
			{
				ft_lstclear_file_lstat(&ls->ls_path, free);
				return (NULL);
			}
		}
		else
		{
			file = true;
			if (!add_to_list(*argv, "", &ls->ls_path))
			{
				ls->flags.print_dir = true;
			}
		}
		argv++;
	}
	if (!file)
	{
		add_to_list(".", "", &ls->ls_path);
	}
	if (IS_DEBUG)
		parse_print(ls);
	return (ls);
}
