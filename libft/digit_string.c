/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:58:16 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 16:01:10 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			digit_string(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (!(ft_isdigit(s[i])))
		{
			if (s[i] != '-' && i != 0)
				return (0);
		}
	}
	return (1);
}