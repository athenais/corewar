/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:59:23 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/11 15:03:59 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>
#include <unistd.h>

int		main(int argc, char **argv)
{
	t_file	file;

	if (argc < 2)
		ft_print_asm_usage();
	else
	{
		if (check_extension(argv[argc - 1]) == EXIT_SUCCESS)
		{
			if (s_to_cor(argv[argc - 1], &file) == EXIT_SUCCESS)
			{
				lseek(file.fd_cor, 0, SEEK_SET);
				write_header(&file);
			}
			close(file.fd_cor);
			free((void *)file.hd);
			free((void *)file.cor);
		}
	}
	return (0);
}
