/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:54:25 by thflahau          #+#    #+#             */
/*   Updated: 2019/08/15 18:27:16 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void					ft_putnstr(char const *str, uint8_t n)
{
	register uint8_t	index;

	index = 0;
	if (!str || !str[0])
		ft_putchar(' ');
	else
	{
		while (index < n && str[index] != 0)
		{
			ft_putchar(ft_printable(str[index]) ? str[index] : '.');
			++index;
		}
	}
}
