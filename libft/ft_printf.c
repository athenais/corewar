/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:15:06 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/15 20:23:07 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>
#define LIKELY(x)		__builtin_expect(!!(x), 1)

int						ft_printf(char const *format, ...)
{
	va_list				list;
	register uint16_t	index;

	index = 0;
	va_start(list, format);
	while (format[index])
	{
		if (format[index] == '%' && LIKELY(format[index + 1] == 's'))
		{
			ft_putstr_fd(va_arg(list, char *), STDERR_FILENO);
			index = index + 2;
		}
		else
			ft_putchar_fd(format[index++], STDERR_FILENO);
	}
	va_end(list);
	return (EXIT_FAILURE);
}
