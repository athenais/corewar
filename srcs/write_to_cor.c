/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:57:08 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/14 16:42:42 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <asm.h>

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

char		*ft_itoa_bse(unsigned int n, int base, int len)
{
	char	*new;
	char	*base_key;

	base_key = "0123456789abcdef";
	if (!(new = ft_strnew(len)))
		return (NULL);
	len--;
	while (len >= 0)
	{
		new[len] = base_key[n % base];
		n /= base;
		len--;
	}
	return (new);
}

/*
**	add dumping!
*/

void		wr_bin(const char *code, t_file *file, uint8_t *buff, int *bit_cnt)
{
	char	c;
	int		bit;

	while ((c = *code))
	{
		bit = c - '0';
		*buff |= bit << (7 - *bit_cnt);
		++(*bit_cnt);
		if (*bit_cnt == 8)
		{
			ft_putchar_fd(*buff, file->fd_cor);
			*buff = 0;
			*bit_cnt = 0;
		}
		code++;
	}
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
	wr_bin(byte_code, file, &buffer, &bit_cnt);
	buffer = 0;
	bit_cnt = 0;
	free((void *)byte_code);
	return (oct / c);
}
