/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:12:00 by cdarrell          #+#    #+#             */
/*   Updated: 2023/07/26 18:00:18 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int	main(int argc, char **argv)
{
	t_ls	*ls;

	(void)argc;
	ls = parse(++argv);
	if (!ls)
		return (1);
	ls_loop(ls);
	ft_lstclear_file_lstat(&ls->ls_path, free);
	free(ls);
	return (0);
}
