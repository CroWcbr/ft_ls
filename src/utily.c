/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utily.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:39:25 by cdarrell          #+#    #+#             */
/*   Updated: 2023/06/18 21:54:27 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <libft.h>

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
