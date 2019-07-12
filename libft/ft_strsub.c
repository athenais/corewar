/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:49:18 by thflahau          #+#    #+#             */
/*   Updated: 2019/04/23 16:26:20 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char					*ft_strsub(char const *str, size_t start, size_t len)
{
	char				*ptr;
	register size_t		index;

	if (str == NULL)
		return (NULL);
	if (!(ptr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	index = 0;
	while (index < len)
	{
		ptr[index] = str[index + start];
		index++;
	}
	ptr[index] = 0;
	return (ptr);
}
