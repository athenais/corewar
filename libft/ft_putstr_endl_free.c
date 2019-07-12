/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_endl_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 10:46:56 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/23 10:47:51 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

inline void					ft_putstr_endl_free(char const *str)
{
	if (__builtin_expect(!!(str != NULL), 1))
	{
		ft_putstr_endl(str);
		free((void *)str);
	}
}
