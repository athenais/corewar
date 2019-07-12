/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fast_bzero.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:30:45 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/24 16:42:31 by thflahau         ###   ########.fr       */
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
