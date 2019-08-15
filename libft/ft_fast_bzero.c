/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fast_bzero.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 18:28:07 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 18:28:42 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void							ft_fast_bzero(void *str, size_t size)
{
	unsigned char				*ptr;
	uint_fast64_t				*addr;

	ptr = (unsigned char *)str;
	while ((((uint_fast64_t)ptr & (sizeof(uint_fast64_t) - 1)) != 0) && size--)
		*ptr++ = 0;
	addr = (uint_fast64_t *)ptr;
	while (size >= sizeof(uint_fast64_t))
	{
		size -= sizeof(uint_fast64_t);
		*addr++ = 0x0UL;
	}
	ptr = (unsigned char *)addr;
	while (size-- > 0)
		*ptr++ = 0;
}
