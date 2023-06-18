/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:11:57 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/18 21:53:38 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>

# define IS_DEBUG 1

typedef struct s_ls
{
	bool	f_l;
	bool	f_big_r;
	bool	f_a;
	bool	f_r;
	bool	f_t;
	t_list	*ls_path;
}			t_ls;

void	ft_err_malloc(char *str);
void	ft_putstr_n(const char *first_arg, ...);
t_ls	*clear_ls(t_ls *ls);

t_ls	*parse(char **argv);

#endif
