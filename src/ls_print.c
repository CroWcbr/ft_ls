/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 00:31:10 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/26 02:04:51 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_print(t_list *lst, t_flags *flags)
{
	while(lst)
	{
		ft_putstr(((t_elem *)lst->content)->name);
		ft_putstr("\n");
		lst = lst->next;
	}
}
