/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:12:00 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/26 02:19:24 by cdarrell         ###   ########.fr       */
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
	ft_lstclear(&ls->ls_path, free);
	free(ls);
	return (0);
}
