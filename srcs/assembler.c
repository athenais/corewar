/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:59:08 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 18:52:47 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <asm_errors.h>

static	t_op const	g_op_tab[] =
{
	{"live", 1, {T_DIR}, 1, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 1},
	{"fork", 1, {T_DIR}, 12, 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 1},
	{"lfork", 1, {T_DIR}, 15, 0, 1},
	{"aff", 1, {T_REG}, 16, 1, 0},
	{0, 0, {0}, 0, 0, 0},
};

void					init_file(t_file *file, int fd, char *file_name)
{
	char	*ptr;

	file->fd = fd;
	file->hd = malloc(sizeof(t_header));
	ft_memset(file->hd, '\0', sizeof(t_header));
	ptr = ft_strrchr(file_name, '.');
	file->cor = ft_strnew(ptr - file_name + 4);
	ft_strncpy(file->cor, file_name, ptr - file_name);
	file->cor = ft_strnjoinfree(file->cor, ".cor", 4);
	file->op_tab = g_op_tab;
	file->label = NULL;
	file->lab_list = NULL;
}

int						s_to_cor(char *file_name, t_file *file)
{
	int					fd;

	if ((fd = open(file_name, O_RDONLY)) == EXIT_ERROR)
		return (ft_puterror(FILERR));
	init_file(file, fd, file_name);
	if ((file->fd_cor = open(file->cor, O_CREAT | O_WRONLY
					| O_TRUNC, 0666)) == EXIT_ERROR)
		return (ft_puterror(FILERR));
	write(file->fd_cor, file->hd, sizeof(t_header));
	return (read_file(file));
}
