/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 17:08:12 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 17:08:50 by abrunet          ###   ########.fr       */
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

uint8_t		get_funptr_index(char *start, t_file *file, int size)
{
	static	int name;
	static	int cmnt;

//	if (file->cmnt == 1)
//		return (2);
	if (*start == '.')
	{
		if (!(ft_strcmp(start, ".name")) && !name)
		{
			name = 1;
			return (1);
		}
		else if (!(ft_strcmp(start, ".comment")) && !cmnt)
		{
			cmnt = 1;
			return (2);
		}
	}
	else if (size > 0 && name && cmnt)
	{
		if (start[size - 1] == ':')
			return (3);
		else if (is_instruction(start, file->op_tab) != EXIT_ERROR)
			return (4);
	}
	return (0);
}
#include <stdio.h>
int			parse_line(t_file *file, char **buff, char *ptr,
	int (**funptr)(t_file *, char **, char *, char **))
{
	static	uint8_t		index;
	char				*start;
	char				*end;

//	printf("here && buffer = %s\n", *buff);
	if (!(get_next_word((char const *)*buff, &start, &end)))
		return (EXIT_SUCCESS);
	if ((index = get_funptr_index(start, file, (int)(end - start))))
	{
		if ((funptr[index])(file, &start, ptr, &end) != EXIT_SUCCESS)
			return (EXIT_ERROR);
		return (parse_line(file, &end, ptr, funptr));
	}
//	if (file->cmnt < 0)
//		return (EXIT_ERROR);
//	if (file->cmnt == 1 || *start == '#' || *start == ';')
	if (*start == '#' || *start == ';')
		return (EXIT_SUCCESS);
	return (ft_puterror(INVLDCHAR));
}

int			read_file(t_file *file)
{
	char				*buffer;
	static char			*string;
	int					ret;
	int					(*funptr[5])(t_file *, char **, char *, char **);

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
