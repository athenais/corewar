/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 23:02:07 by abrunet           #+#    #+#             */
/*   Updated: 2017/11/22 20:42:54 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		size_n(int n)
{
	size_t i;

	i = 0;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	i++;
	return (i);
}

static char			*n_is_pos(char *s, int n, size_t i)
{
	size_t j;

	j = 0;
	if (i > size_n(n))
	{
		s[0] = '-';
		j += 1;
	}
	i -= 2;
	while (n > 0)
	{
		s[i] = (n % 10) + '0';
		i--;
		j++;
		n = n / 10;
	}
	s[j] = '\0';
	return (s);
}

char				*ft_itoa(int n)
{
	char	*s;
	size_t	i;

	i = size_n(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s = (char *)malloc(i + 1);
	if (!s)
		return (NULL);
	if (n == 0)
	{
		ft_memset(s, '0', 1);
		s[1] = '\0';
		return (s);
	}
	if (n < 0)
	{
		i += 1;
		n *= -1;
	}
	if (n > 0)
		s = n_is_pos(s, n, i);
	return (s);
}
