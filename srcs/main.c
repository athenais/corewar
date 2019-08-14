/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:59:23 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/14 16:05:42 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>
#include <stdarg.h>
#include <unistd.h>

void					ft_dprintf(int fd, char const *fmt, ...)
{
	va_list				list;
	char				*string;

	va_start(list, fmt);
	while (*fmt != 0)
	{
		if (*fmt == '%' && *(fmt + 1) == 's')
		{
			if ((string = va_arg(list, char *)) != NULL)
				write(fd, string, ft_strlen(string));
			fmt += 2;
		}
		else
			write(fd, fmt++, 1);
	}
	va_end(list);
}

int		main(int argc, char **argv)
{
	t_file	file;

	if (argc < 2)
		ft_print_asm_usage();
	else
	{
		if (check_extension(argv[argc - 1]) == EXIT_SUCCESS)
		{
			file.fd_cor = 0;
			if (s_to_cor(argv[argc - 1], &file) == EXIT_SUCCESS)
			{		
				lseek(file.fd_cor, 0, SEEK_SET);
				write_header(&file);
				ft_dprintf(1, "writing output to %s\n", file.cor);
			}
			if (file.fd_cor)
				close(file.fd_cor);
			free((void *)file.hd);
			free((void *)file.cor);
		}
	}
	return (EXIT_SUCCESS);
}
