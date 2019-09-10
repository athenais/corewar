/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:08:12 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/09 19:34:36 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <asm_errors.h>

int			is_instruction(char *str, t_op const *op_tab)
{
	int		index;

	index = -1;
	while (op_tab[++index].name)
	{
		if (!(ft_strcmp(str, op_tab[index].name)))
			return (index);
	}
	return (EXIT_ERROR);
}

#include <stdio.h>
int			check_header_var(int *name, int *cmnt, char **start, char **end)
{
	int		size;

	if	(!(*name)
		&& !(ft_strncmp(*start, ".name", (size = ft_strlen(".name")))))
	{
		*name = 1;
		*end = *start + size;
		return (1);
	}
	else if	(!(*cmnt)
		&& !(ft_strncmp(*start, ".comment", (size = ft_strlen(".comment")))))
	{
		*cmnt = 1;
		*end = *start + size;
		return (2);
	}
	return (0);
}

uint8_t		get_funptr_index(char **start, char **end, t_file *file)
{
	static	int name;
	static	int cmnt;
	char	s[INST_MAX_SIZE];
	int		i;

	i = 0;
	ft_fast_bzero(s, INST_MAX_SIZE);
	if (**start == '.')
		return (check_header_var(&name, &cmnt, start, end));
	else if (name && cmnt)
	{
		while ((*start)[i] && !ft_iswhitespace((*start)[i])
			&& (*start)[i] != ':' && (*start)[i] != '%')
			i++;
		if ((*start)[i] == ':')
		{
			*end = *start + i + 1;
			return (3);
		}
		else if (i < INST_MAX_SIZE && (*start)[i]
			&& (ft_iswhitespace((*start)[i]) || (*start)[i] == '%'))
		{
			ft_strncpy(s, (*start), i);
			if (is_instruction(s, file->op_tab) != EXIT_ERROR)
			{
				*end = *start + i;
				*start = s;
				return (4);
			}
		}
	}
	return (0);
}
int			parse_line(t_file *file, char **buff, char *ptr,
	int (**funptr)(t_file *, char **, char **))
{
	static	uint8_t		index;
	int					i;
	char				*start;
	char				*end;

	i = 0;
	while (*buff && ft_iswhitespace((*buff)[i]))
		i++;
	if (!(*buff) || !(*buff)[i])
		return(EXIT_SUCCESS);
	start = *buff + i;
//	printf("|%s| = buffer\n", *buff);
	if (file->cmnt == 1)
	{
		start = *buff;
		end = ptr;
	}
	index = (file->cmnt) ? 2
		: get_funptr_index(&start, &end, file);
//	printf("%d = index\n", index);
	if (index)
	{
		if ((funptr[index])(file, &start, &end) != EXIT_SUCCESS)
			return (EXIT_ERROR);
		return ((file->cmnt) ? EXIT_SUCCESS
				: parse_line(file, &end, ptr, funptr));
	}
	if (file->cmnt < 0)
		return (EXIT_ERROR);
	if (*start == '#' || *start == ';')
		return (EXIT_SUCCESS);
	return (ft_puterror(INVLDCHAR));
}

int			read_file(t_file *file)
{
	char				*buffer;
	static char			*string;
	int					ret;
	int					(*funptr[5])(t_file *, char **, char **);

	file->line = 1;
	funptr[1] = &get_champ_name;
	funptr[2] = &get_comment;
	funptr[3] = &get_label;
	funptr[4] = &get_instruction;
	file->bytes = 0;
	if (!(string = ft_strnew(1)))
		return (EXIT_ERROR);
	while ((ret = ft_readline(file->fd, &string, &buffer)) > 0)
	{
		if (parse_line(file, &buffer, buffer + (ret - 1), funptr) == EXIT_ERROR)
		{
			free((void *)buffer);
			return (EXIT_ERROR);
		}
		file->line++;
		free((void *)buffer);
	}
	free((void *)buffer);
	return (EXIT_SUCCESS);
}
