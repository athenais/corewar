/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 19:50:32 by abrunet           #+#    #+#             */
/*   Updated: 2017/11/22 22:50:29 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(char const *str, int c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str != c && (!*(str + 1) || *(str + 1) == c))
			count++;
		str++;
	}
	return (count);
}

static int		word_length(char const *s, char c, size_t last_i)
{
	int wrdlen;

	wrdlen = 0;
	while (s[last_i] != c && s[last_i])
	{
		wrdlen++;
		if (s[last_i] == '\0')
			wrdlen++;
		last_i++;
	}
	return (wrdlen);
}

static void		free_splitend(char ***splitend, int last_i)
{
	while (last_i >= 0)
	{
		free(*splitend[last_i]);
		last_i--;
	}
	free(*splitend);
	*splitend = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char	**splitend;
	size_t	i;
	int		wrdlen;
	size_t	last_i;

	if (!s)
		return (NULL);
	last_i = 0;
	i = 0;
	if (!(splitend = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1))))
		return (NULL);
	while ((int)i < ft_count(s, c) && *s)
	{
		while (s[last_i] == c && s[last_i] != '\0')
			last_i++;
		wrdlen = word_length(s, c, last_i);
		if (!(splitend[i] = (char *)malloc(wrdlen + 1)))
			free_splitend(&splitend, last_i);
		ft_strncpy(splitend[i], s + last_i, wrdlen);
		splitend[i][wrdlen] = '\0';
		last_i += wrdlen;
		i++;
	}
	splitend[i] = NULL;
	return (splitend);
}
