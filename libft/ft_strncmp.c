/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 22:37:33 by abrunet           #+#    #+#             */
/*   Updated: 2017/11/23 16:03:20 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;
	size_t			res;

	i = 0;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	res = 0;
	if (n != 0)
	{
		while (s1[i] == s2[i] && s2[i] != '\0' && s2[i] != '\0' && (i + 1) < n)
			i++;
		res = (s1[i] - s2[i]);
	}
	return (res);
}
