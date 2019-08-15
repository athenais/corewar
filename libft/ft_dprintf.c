/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:53:40 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 15:56:23 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include <unistd.h>

void					ft_dprintf(int fd, char const *fmt, ...)
{
	va_list				list;
	char				*string;

	va_start(list, fmt);
	while (*fmt != 0)
	{
		if (*fmt == '%' && *(fmt + 1) == 's')
		{
			if ((string = va_arg(list, char *)) != NULL)
				write(fd, string, ft_strlen(string));
			fmt += 2;
		}
		else
			write(fd, fmt++, 1);
	}
	va_end(list);
}
