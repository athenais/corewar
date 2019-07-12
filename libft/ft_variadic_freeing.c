/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variadic_freeing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:53:55 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/16 16:22:05 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>

/*
**	Prend en premier paramètre le nombre de pointeurs à libérer et
**	libère chaque pointeur tour à tour.
*/

uint8_t				ft_variadic_freeing(unsigned int nb, ...)
{
	void			*ptr;
	va_list			args;
	uint8_t			index;

	index = 0;
	va_start(args, nb);
	while (index++ < nb)
		if ((ptr = va_arg(args, void *)) != NULL)
			free(ptr);
	va_end(args);
	return (EXIT_FAILURE);
}
