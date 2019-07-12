/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:53:14 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/18 20:29:10 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static inline uint16_t	ft_integer_length(uint16_t nb)
{
	uint16_t			length;

	length = 1;
	while ((nb /= 10))
		++length;
	return (length);
}

void					ft_putnbr_light(uint16_t nb)
{
	char				*str;
	uint16_t			length;

	length = ft_integer_length(nb);
	if (!(str = (char *)malloc(sizeof(char) * (length + 1))))
		return ;
	str[length] = 0;
	while (nb && length)
	{
		str[--length] = nb % 10 + 48;
		nb = nb / 10;
	}
	ft_putstr(str);
	free((void *)str);
}
