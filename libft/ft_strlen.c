/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:54:51 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/23 16:07:41 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#define LIKELY(x)		__builtin_expect(!!(x), 1)

inline size_t			ft_strlen(char const *str)
{
	char				*ptr;

	ptr = (char *)str;
	while (LIKELY(*ptr))
		ptr++;
	return (ptr - str);
}
