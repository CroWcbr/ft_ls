/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:00:13 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/18 21:58:28 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	ls_print(t_ls *ls)
{
	t_list	*tmp;

	ft_putstr("flag : \n");
	ft_putstr("\t\tl\t:\t");
	ft_putnbr_fd(ls->f_l, 1);
	ft_putstr("\n\t\tR\t:\t");
	ft_putnbr_fd(ls->f_big_r, 1);
	ft_putstr("\n\t\ta\t:\t");
	ft_putnbr_fd(ls->f_a, 1);
	ft_putstr("\n\t\tr\t:\t");
	ft_putnbr_fd(ls->f_r, 1);
	ft_putstr("\n\t\tt\t:\t");
	ft_putnbr_fd(ls->f_t, 1);
	ft_putstr("\ndir for ls :");
	tmp = ls->ls_path;
	while (tmp)
	{
		ft_putstr("\n\t\t");
		ft_putstr((char *)tmp->content);
		tmp = tmp->next;
	}
	ft_putstr("\n");
}

static t_ls	*init(void)
{
	t_ls	*ls;

	ls = malloc(sizeof(t_ls));
	if (!ls)
		ft_err_malloc("Error malloc: parse.c - init - ls");
	ls->f_l = false;
	ls->f_big_r = false;
	ls->f_a = false;
	ls->f_r = false;
	ls->f_t = false;
	ls->ls_path = NULL;
	return (ls);
}

static void	add_to_list(char *str_to_list, t_list **list)
{
	char	*tmp;
	t_list	*new_list;

	tmp = ft_strdup(str_to_list);
	if (!tmp)
		ft_err_malloc("Error malloc: parse.c - add_to_list - tmp");
	new_list = ft_lstnew(tmp);
	if (!new_list)
		ft_err_malloc("Error malloc: parse.c - add_to_list - new_list");
	ft_lstadd_back(list, new_list);
}

static bool	parse_flag(char *flags, t_ls *ls)
{
	while (*flags)
	{
		if (*flags == 'l')
			ls->f_l = true;
		else if (*flags == 'R')
			ls->f_big_r = true;
		else if (*flags == 'a')
			ls->f_a = true;
		else if (*flags == 'r')
			ls->f_r = true;
		else if (*flags == 't')
			ls->f_t = true;
		else
		{
			ft_putstr_n("ft_ls: invalid option: ", flags, "\n");
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
			add_to_list(*argv, &ls->ls_path);
		argv++;
	}
	if (!ls->ls_path)
		add_to_list(".", &ls->ls_path);
	if (IS_DEBUG)
		ls_print(ls);
	return (ls);
}
