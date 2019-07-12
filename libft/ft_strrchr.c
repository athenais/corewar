/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:32:16 by abrunet           #+#    #+#             */
/*   Updated: 2017/11/22 20:35:14 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*tmp;

	tmp = NULL;
	while (*str)
	{
		if (*str == c)
			tmp = (char *)str;
		str++;
	}
	if (*str == c)
		tmp = (char *)str;
	return (tmp);
}
