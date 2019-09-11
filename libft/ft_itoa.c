/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 23:02:07 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 22:20:42 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_digitcount_base(unsigned int n, int base)
{
	int i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		i++;
		n /= base;
	}
	return (i);
}

int			ft_digitcount(unsigned int n)
{
	return (ft_digitcount_base(n, 10));
}

char		*ft_itoa(int n)
{
	char	*new;
	int		len;
	int		start;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = (n < 0) ? ft_digitcount(n * -1) + 1 : ft_digitcount(n);
	if (!(new = ft_strnew(len)))
		return (NULL);
	start = (n < 0);
	if (n < 0)
	{
		n *= -1;
		new[0] = '-';
	}
	len--;
	while (len >= start)
	{
		new[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (new);
}
