/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:15:00 by thflahau          #+#    #+#             */
/*   Updated: 2019/05/23 12:52:07 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>

#define UNLIKELY(x)			__builtin_expect(!!(x), 0)

int							ft_readline(int fd, char **string, char **line)
{
	char					buffer[BUFF_SIZE];
	char					*ptr;
	register ssize_t		bytes;

	while (!ft_strchr(*string, 10) && (bytes = read(fd, buffer, BUFF_SIZE)) > 0)
		if (!(*string = ft_strnjoinfree(*string, buffer, bytes)))
			return (-1);
	bytes = 0;
	while ((*string)[bytes] && (*string)[bytes] != '\n')
		++bytes;
	if (UNLIKELY((*line = ft_strndup(*string, bytes)) == NULL))
		return (-1);
	if ((*string)[bytes] == '\n')
		++bytes;
	ptr = *string;
	if (UNLIKELY((*string = ft_strdup(ptr + bytes)) == NULL))
		return (-1);
	free((void *)ptr);
	return (bytes > 0 ? bytes : 0);
}
