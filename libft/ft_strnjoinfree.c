/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoinfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:55:40 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/10 19:12:10 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char				*ft_strnjoinfree(char const *s1, char const *s2, size_t n)
{
	char			*str;
	char			*ptr;
	char			*tmp;

	if (!s1 || !s2)
		return (NULL);
	tmp = (char *)s1;
	if (!(str = ft_strnew(ft_strlen(s1) + n + 1)))
		return (NULL);
	ptr = str;
	while (*s1)
		*str++ = *s1++;
	while (n-- > 0 && *s2)
		*str++ = *s2++;
	*str = 0;
	free((void *)tmp);
	return (ptr);
}
