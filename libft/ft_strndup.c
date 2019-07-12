/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:09:42 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/10 19:10:15 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char					*ft_strndup(char const *src, size_t n)
{
	char				*str;
	char				*ptr;

	if (!(str = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	ptr = str;
	while (n-- > 0)
		*str++ = *src++;
	*str = 0;
	return (ptr);
}
