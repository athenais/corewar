#include <stdio.h>
#include <asm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <asm_errors.h>

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

int						parse_line(t_file *file, char **buff, char *ptr,
	int (**funptr)(t_file *, char **, char *, char **))
{
	static	uint8_t		index;
	char				*start;
	char				*end;

	if (!(get_next_word((char const *)*buff, &start, &end)))
		return (EXIT_SUCCESS);
	if ((index = get_funptr_index(start, file, (int)(end - start))))
	{	
		if ((funptr[index])(file, &start, ptr, &end) != EXIT_SUCCESS)
			return (EXIT_ERROR);
		printf("buff = |%s|\n", end);
		return (parse_line(file, &end, ptr, funptr));
	}
	if (*start == '#')
		return (EXIT_SUCCESS);
	return (ft_puterror(INVLDCHAR));
}

int						read_file(t_file *file)
{
	char				*buffer;
	static char			*string;
	int					ret;
	int					(*funptr[5])(t_file *, char **, char *, char **);

	funptr[1] = &get_champ_name;
	funptr[2] = &get_comment;
	funptr[3] = &get_label;
	funptr[4] = &get_instruction;
	file->bytes = 0;
	if (!(string = ft_strnew(1)))
		return (EXIT_ERROR);
	while ((ret = ft_readline(file->fd, &string, &buffer)) > 0)
	{
		file->bytes += ret;
		file->str_len = (off_t)ft_strlen(string);
		printf("BUFFER = |%s|\n", buffer);
		if (parse_line(file, &buffer, buffer + (ret - 1), funptr) == EXIT_ERROR)
			return (EXIT_ERROR);
		free((void *)buffer);
	}
	return (EXIT_SUCCESS);	
}

int						s_to_cor(char *file_name)
{
	t_file 				file;
	char				*ptr;
//check if bzero (+1);

	if ((file.fd = open(file_name, O_RDONLY)) == EXIT_ERROR)
		return (ft_puterror(FILERR));
	//make function
	file.hd = malloc(sizeof(header_t));
	ptr = ft_strrchr(file_name, '.');
	file.cor = ft_strnew(ptr - file_name + 4);
	ft_strncpy(file.cor, file_name, ptr - file_name);
	file.cor = ft_strnjoinfree(file.cor, ".cor", 4);
	if ((file.fd_cor = open(file.cor, O_CREAT | O_RDWR, 0666)) == EXIT_ERROR)
		return (ft_puterror(FILERR));
	file.label = NULL;
//	write_to_cor(COREWAR_EXEC_MAGIC, i, &file);
	ft_bzero(file.hd->prog_name, PROG_NAME_LENGTH);
	ft_bzero(file.hd->comment, COMMENT_LENGTH);
	define_op_tab(&file.op_tab);
	return (read_file(&file));
}
