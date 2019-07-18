#include <stdio.h>
#include <asm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include <asm_errors.h>

uint8_t					is_instruction(char *str, t_op *op_tab)
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

uint8_t					get_funptr_index(char *start, t_file *file, int size)
{
	static	int name;
	static	int cmnt;

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

int						read_line(t_file *file, char **buff, char *ptr)
{
	static	uint8_t		index;
	char				*start;
	char				*end;
	uint8_t				(*funptr[4])(t_file *, char *, char *, char *);

	funptr[1] = &get_champ_name;
	funptr[2] = &get_comment;
//	funptr[3] = &get_label;
//	funptr[4] = &get_instruction;
	*ptr = '\0';
	get_next_word((char const *)*buff, &start, &end);
	if ((index = get_funptr_index(start, file, (int)(end - start))))
	{
		(funptr[index])(file, start, ptr, end);
		printf("|%s| = champ\n", file->cmnt);
		*buff = (ptr)
			? ft_strcpy(*buff, (char const *)ptr + 1) : '\0';
	}
	return (EXIT_ERROR);
}

int						read_file(t_file *file, char **buffer)
{
	int 				ret;
	int 				lp;
	int 				bit_rd;
	char 				*ptr;
//add read(fd) error
//check if buffer empty, add diff
//add gnl_cap
	ret = read(file->fd, *buffer, BUF_SIZE);
	bit_rd = ret;
	lp = 1;
	//protection on lp??
	while (!(ptr = ft_strchr(*buffer, '\n')) && ret)
	{
		lp++;
		if (!(*buffer = realloc(*buffer, BUF_SIZE * lp + 1)))
		{
				return (EXIT_ERROR);
		}
		ft_bzero(*buffer + (BUF_SIZE * (lp - 1)), BUF_SIZE + 1);
		ret = read(file->fd, *buffer + (BUF_SIZE * (lp - 1)), BUF_SIZE);
		bit_rd += ret;
	}
	read_line(file, buffer, ptr);  
	return (0);	
}

int						translate_to_cor(char *file_name)
{
	char 				*buffer;
	t_file 				file;

	if ((file.fd = open(file_name, O_RDONLY)) == EXIT_ERROR)
	{
		//error file msg ?
		return (EXIT_ERROR);
	}
	define_op_tab(&file.op_tab);
	buffer = (char *)malloc(sizeof(char) * BUF_SIZE + 1);
	ft_bzero(buffer, BUF_SIZE + 1);
	read_file(&file, &buffer);
	return (EXIT_SUCCESS);
}
