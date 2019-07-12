/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u32len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:07:57 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/31 15:10:51 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

inline uint16_t				ft_u32len(uint32_t nb)
{
	if (nb >= 10000)
		return (5);
	else if (nb >= 1000)
		return (4);
	else if (nb >= 100)
		return (3);
	else if (nb >= 10)
		return (2);
	return (1);
}
