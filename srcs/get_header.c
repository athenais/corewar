/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:57:35 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/09 19:47:59 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <asm_errors.h>
#include <stdio.h>

int		get_champ_name(t_file *file, char **wd, char **end)
{
	char	*p;
	int		size;

	(void)*wd;
	while (**end && (ft_iswhitespace(**end)))
		(*end)++;
	if (**end == '"')
	{
		if ((p = ft_strchr(*end + 1, '"')))
		{
			if ((size = (int)(p - (*end + 1))) > PROG_NAME_LENGTH)
				return (ft_puterror(LNAME));
			ft_strncpy(file->hd->prog_name, *end + 1, size);
			*end = p + 1;
			return (EXIT_SUCCESS);
		}
	}
	return (ft_puterror(BADNAME));
}

int		check_multiple_line_cmnt(char **end, char **wd, t_file *file)
{
	char		*p;
	char const	*s;

	s = (file->cmnt == 1) ? *wd : *end + 1;
	if ((p = ft_strchr(s, '"')))
		file->tmp = ft_strnjoinfree(file->tmp, s, (size_t)(p - (s)));
	else
	{
		file->cmnt = 1;
		file->tmp = ft_strnjoinfree(file->tmp, s, ft_strlen((s)));
		file->tmp = ft_strnjoinfree(file->tmp, "\n", 1);
	}
	if (ft_strlen(file->tmp) > COMMENT_LENGTH && (file->cmnt = -1))
		return (ft_puterror(LCMNT));
	if (p)
	{
		file->cmnt = 0;
		ft_strcpy(file->hd->comment, file->tmp);
		free(file->tmp);
		*end = p + 1;
	}
	else
		*end += ft_strlen(s) + 1;
	return (EXIT_SUCCESS);
}

int		get_comment(t_file *file, char **wd, char **end)
{
	if (!file->cmnt)
	{
		while (**end && (ft_iswhitespace(**end)))
			(*end)++;
	}
	if (**end == '"' || file->cmnt == 1)
		return (check_multiple_line_cmnt(end, wd, file));
	file->cmnt = -1;
	return (ft_puterror(BADCMNT));
}
