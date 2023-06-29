/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utily.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:39:25 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/29 02:25:00 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../external/libft/include/libft.h>
#include <stdarg.h>

void	ft_err_malloc(char *str)
{
	ft_putstr(str);
	exit (1);
}

void	ft_putstr_n(char *first_arg, ...)
{
	va_list	args;
	char	*arg;

	va_start(args, first_arg);
	arg = first_arg;
	while (*arg)
	{
		write(1, arg, ft_strlen(arg));
		arg = va_arg(args, char *);
	}
	va_end(args);
}

char	*path_to_file(char* dir_path, char* file_path)
{
	char	*new_path;
	char	*tmp;

	if (dir_path[0] == '\0')
		new_path = ft_strdup(file_path);
	else if (dir_path[ft_strlen(dir_path) - 1] == '/')
		new_path = ft_strjoin(dir_path, file_path);
	else
	{
		tmp = ft_strjoin(dir_path, "/");
		if (!tmp)
		{
			ft_putstr("Error malloc: utily.c - path_to_file - tmp\n");
			exit(-1);
		}
		new_path = ft_strjoin(tmp, file_path);
		free(tmp);
	}
	if (!new_path)
	{
		ft_putstr("Error malloc: utily.c - path_to_file - new_path\n");
		exit(-1);
	}
	return new_path;
}

void	add_char_to_list(char *str_to_list, t_list **list)
{
	char	*tmp;
	t_list	*new_list;

	tmp = ft_strdup(str_to_list);
	if (!tmp)
	{
		ft_putstr("Error malloc: utily_lst.c - add_to_list - tmp\n");
		exit(-1);
	}
	new_list = ft_lstnew(tmp);
	if (!new_list)
	{
		ft_putstr("Error malloc: utily_lst.c - add_to_list - new_list\n");
		exit(-1);
	}
	ft_lstadd_back(list, new_list);
}