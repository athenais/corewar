/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:08:12 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 14:33:08 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <asm_errors.h>

int			check_valid_inst_index(char **start,
		int i, t_file *file, char **end)
{
	char	s[INST_MAX_SIZE];

	if (!file->op)
		file->op = 1;
	ft_fast_bzero(s, INST_MAX_SIZE);
	ft_strncpy(s, (*start), i);
	if (is_instruction(s, file->op_tab) != EXIT_ERROR)
	{
		*end = *start + i;
		*start = s;
		return (1);
	}
	return (0);
}

uint8_t		get_funptr_index(char **start, char **end, t_file *file)
{
	static int		name;
	static int		cmnt;
	int				i;

	if (**start == '.')
		return (check_header_var(&name, &cmnt, start, end));
	else if (name && cmnt)
	{
		i = get_end_word_index(start);
		if ((*start)[i] == ':')
		{
			*end = *start + i + 1;
			return (3);
		}
		else if (i < INST_MAX_SIZE && (*start)[i]
			&& (ft_iswhitespace((*start)[i]) || (*start)[i] == '%'))
			if (check_valid_inst_index(start, i, file, end))
				return (4);
	}
	return (0);
}

int			get_end_and_start(char **end, char **start,
		char **buff, t_file *file)
{
	int		i;

	i = 0;
	if (file->cmnt == 1)
	{
		*start = *buff;
		*end += ft_strlen(*start);
	}
	else
	{
		while (*buff && ft_iswhitespace((*buff)[i]))
			i++;
		if (!(*buff) || !(*buff)[i])
			return (1);
		*start = *buff + i;
	}
	return (0);
}

int			parse_line(t_file *file, char **buff, char *ptr,
	int (**funptr)(t_file *, char **, char **))
{
	static	uint8_t		index;
	char				*start;
	char				*end;

	if (get_end_and_start(&end, &start, buff, file))
		return (EXIT_SUCCESS);
	index = (file->cmnt) ? 2
		: get_funptr_index(&start, &end, file);
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
