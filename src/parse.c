/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:00:13 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/26 02:10:39 by cdarrell         ###   ########.fr       */
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
	ft_putnbr_fd(ls->flags.f_big_r, 1);
	ft_putstr("\n\t\ta\t:\t");
	ft_putnbr_fd(ls->flags.f_a, 1);
	ft_putstr("\n\t\tr\t:\t");
	ft_putnbr_fd(ls->flags.f_r, 1);
	ft_putstr("\n\t\tt\t:\t");
	ft_putnbr_fd(ls->flags.f_t, 1);
	ft_putstr("\ndir for ls :");
	tmp = ls->ls_path;
	while (tmp)
	{
		ft_putstr("\n\t\t");
		ft_putstr((char *)tmp->content);
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
	ls->flags.f_big_r = false;
	ls->flags.f_a = false;
	ls->flags.f_r = false;
	ls->flags.f_t = false;
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
		"\0"
	);
}

static bool	parse_flag(char *flags, t_ls *ls)
{
	while (*flags)
	{
		if (*flags == 'l')
			ls->flags.f_l = true;
		else if (*flags == 'R')
			ls->flags.f_big_r = true;
		else if (*flags == 'a')
			ls->flags.f_a = true;
		else if (*flags == 'r')
			ls->flags.f_r = true;
		else if (*flags == 't')
			ls->flags.f_t = true;
		else if (*flags == 'f')
			ls->flags.f_f = true;
		else if (*flags == 'h')
		{
			print_usage();
			return (false);
		}
		else
		{
			ft_putstr_n("ft_ls: invalid option: ", flags, "\n", \
						"Try 'ls -h' for more information.\n","\0");
			return (false);
		}
		flags++;
	}
	return (true);
}

t_ls	*parse(char **argv)
{
	t_ls	*ls;

	ls = init();
	while (*argv)
	{
		if ((*argv)[0] == '-' && (*argv)[1])
		{
			if (!parse_flag(++(*argv), ls))
			{
				ft_lstclear(&ls->ls_path, free);
				return (NULL);
			}
		}
		else
			add_char_to_list(*argv, &ls->ls_path);
		argv++;
	}
	if (!ls->ls_path)
		add_char_to_list(".", &ls->ls_path);
	if (IS_DEBUG)
		parse_print(ls);
	return (ls);
}
