#include <stdio.h>
#include <asm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include <asm_errors.h>

//have struct file w/ fd, t_header, 
//struct label, keep track of existing labels with hexcode;
//
int		read_line(int fd, char **buff, char *ptr, int br)
{
	fd = 0;
	br = 0;
	*ptr = '\0';
	//divide into words, have strip func ready, if ".", comment//
	//malloc = label, struct,
	*buff = (ptr) ? ft_strcpy(*buff, (char const *)ptr + 1) : '\0';	
	return (EXIT_SUCCESS);
}

int		read_file(int fd, char **buffer)
{
	int ret;
	int lp;
	int bit_rd;
	char *ptr;
//add read(fd) error
	ret = read(fd, *buffer, BUF_SIZE);
	bit_rd = ret;
	lp = 1;
	while (!(ptr = ft_strchr(*buffer, '\n')) && ret)
	{
		lp++;
		if (!(*buffer = realloc(*buffer, BUF_SIZE * lp + 1)))
		{
				return (EXIT_ERROR);
		}
		ft_bzero(*buffer + (BUF_SIZE * (lp - 1)), BUF_SIZE + 1);
		ret = read(fd, *buffer + (BUF_SIZE * (lp - 1)), BUF_SIZE);
		bit_rd += ret;
	}
	read_line(fd, buffer, ptr, bit_rd);  
	return (0);	
}

int		translate_to_cor(char *file_name)
{
	int	fd;
	char *buffer;

	if ((fd = open(file_name, O_RDONLY)) == EXIT_ERROR)
	{
		//error file msg ?
		return (EXIT_ERROR);
	}
	buffer = (char *)malloc(sizeof(char) * BUF_SIZE + 1);
	ft_bzero(buffer, BUF_SIZE + 1);
	read_file(fd, &buffer);
	return (EXIT_SUCCESS);
}
