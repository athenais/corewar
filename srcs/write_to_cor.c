/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:57:08 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 22:12:31 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <asm.h>
#include <asm_errors.h>
#include <fcntl.h>

void		write_string(t_file *file, int len)
{
	int		size;
	char	*str;

	str = (len == COMMENT_LENGTH) ? file->hd->comment : file->hd->prog_name;
	size = ft_strlen(str);
	while (*str)
	{
		write_to_cor((int)*str, c, file);
		str++;
	}
	while (size < len)
	{
		write_to_cor('\0', c, file);
		size++;
	}
}

void		write_header(t_file *file)
{
	write_to_cor(COREWAR_EXEC_MAGIC, i, file);
	write_string(file, PROG_NAME_LENGTH);
	write_to_cor('\0', i, file);
	write_to_cor(file->hd->prog_size, i, file);
	write_string(file, COMMENT_LENGTH);
}

int			write_to_cor_file(t_file *file)
{
	unsigned int	i;

	i = -1;
	if ((file->fd_cor = open(file->cor, O_CREAT | O_WRONLY
		| O_TRUNC, 0666)) == EXIT_ERROR)
		return (ft_puterror(FILERR, file->line));
	write(file->fd_cor, file->hd, sizeof(t_header));
	while (++i < file->hd->prog_size)
		ft_putchar_fd(file->wr_buff[i], file->fd_cor);
	if (parse_lab_list(file) != EXIT_SUCCESS)
		return (EXIT_ERROR);
	lseek(file->fd_cor, 0, SEEK_SET);
	write_header(file);
	return (EXIT_SUCCESS);
}

int			wr_bin(const char *code, t_file *file, uint8_t *buff, int *bit_cnt)
{
	char		c;
	int			bit;
	static	int size;

	while ((c = *code))
	{
		bit = c - '0';
		*buff |= bit << (7 - *bit_cnt);
		++(*bit_cnt);
		if (*bit_cnt == 8)
		{
			if (!file->wr)
				file->wr_buff[size] = *buff;
			else
				ft_putchar_fd(*buff, file->fd_cor);
			*buff = 0;
			*bit_cnt = 0;
			if (!file->wr && size++ == CHMP_BUFF)
				return (ft_puterror(CHAMPSIZERR, file->line));
		}
		code++;
	}
	return (EXIT_SUCCESS);
}

int			write_to_cor(unsigned int byte, int oct, t_file *file)
{
	char	*byte_code;
	int		bit_cnt;
	uint8_t	buffer;

	buffer = 0;
	bit_cnt = 0;
	if (!(byte_code = ft_itoa_bse(byte, 2, oct)))
		return (-1);
	if (wr_bin(byte_code, file, &buffer, &bit_cnt) < 0)
		return (-1);
	buffer = 0;
	bit_cnt = 0;
	free((void *)byte_code);
	return (oct / c);
}
