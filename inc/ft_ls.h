/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:11:57 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/26 02:16:55 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

# define IS_DEBUG 1

typedef struct	s_flags
{
	bool	f_l;
	bool	f_big_r;
	bool	f_a;
	bool	f_r;
	bool	f_t;
	bool	f_f;
} t_flags;

typedef struct	s_ls
{
	t_flags	flags;
	t_list	*ls_path;
} t_ls;

typedef struct	s_elem
{
	char*	name;
	time_t	modified_time;
} t_elem;

void	ft_err_malloc(char *str);
void	ft_putstr_n(const char *first_arg, ...);

//lst
void	add_char_to_list(char *str_to_list, t_list **list);
void	add_elem_to_list(char *name, time_t modified_time, t_list **list);
void	ft_lstclear_elem(t_list **lst);

t_ls	*parse(char **argv);
void	ls_loop(t_ls *ls);
void	ls_sort(t_list **lst, t_flags *flags);
void	ls_print(t_list *lst, t_flags *flags);

#endif
