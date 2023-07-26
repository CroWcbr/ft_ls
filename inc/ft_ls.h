/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:11:57 by cdarrell          #+#    #+#             */
/*   Updated: 2023/07/27 01:28:45 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../external/libft/include/libft.h"
# include <stdbool.h>
#include <sys/stat.h>

# define IS_DEBUG 0

# define	RED		"\033[31m"
# define	GREEN	"\033[32m"
# define	BLUE	"\033[34m"
# define	PURPLE	"\033[35m"
# define	CYON	"\033[36m"
# define	WHITE	"\033[0m"

typedef struct	s_flags
{
//mandatory
	bool	f_l;
	bool	f_R;
	bool	f_a;
	bool	f_r;
	bool	f_t;

//bonus
	bool	f_color;
	bool	f_A;
	bool	f_d;
	bool	f_g;
	bool	f_i;
	bool	f_m;
	bool	f_n;
	bool	f_o;
	bool	f_s;
	bool	f_S;
	bool	f_U;

//help
	bool	print_file;
	bool	print_endl;
	bool	print_dir;
} t_flags;

typedef struct	s_file_lstat
{
	char		*file_name;
	char		*full_path;
	struct stat	file_stat;
} t_file_lstat;

typedef struct	s_ls
{
	t_flags	flags;
	t_list	*ls_path;
} t_ls;

//utils
void	ft_err_malloc(char *str);
void	ft_putstr_n(char *first_arg, ...);

//lst
char	*path_to_file(char *dir_path, char *file_path);
bool	add_to_list(char *str_to_list, char *path, t_list **list);
void	ft_lstclear_file_lstat(t_list **lst, void (*del)(void*));
// void	add_char_to_list(char *str_to_list, t_list **list);

//ls
t_ls	*parse(char **argv);
void	ls_loop(t_ls *ls);
void	ls_sort(t_list **lst, t_flags *flags);
void	ls_print(t_list *lst, t_flags *flags, char *path);

#endif
