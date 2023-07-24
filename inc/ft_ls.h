/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:11:57 by cdarrell          #+#    #+#             */
/*   Updated: 2023/07/23 22:07:52 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../external/libft/include/libft.h"
# include <stdbool.h>

# define IS_DEBUG 1

typedef struct	s_flags
{
	bool	f_l;
	bool	f_R;
	bool	f_a;
	bool	f_r;
	bool	f_t;
	bool	f_f;
	bool	print_endl;
	bool	print_dir;
} t_flags;

typedef struct	s_ls
{
	t_flags	flags;
	t_list	*ls_path;
} t_ls;

void	ft_err_malloc(char *str);
void	ft_putstr_n(const char *first_arg, ...);

//lst
void	add_char_to_list(char *str_to_list, t_list **list);
char	*path_to_file(char *dir_path, char *file_path);

t_ls	*parse(char **argv);
void	ls_loop(t_ls *ls);
void	ls_sort(t_list **lst, t_flags *flags, char *path);
void	ls_print(t_list *lst, t_flags *flags, char *path);

#endif
