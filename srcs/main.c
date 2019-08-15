/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:59:23 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 19:07:26 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <unistd.h>
#include <asm.h>

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
			free_label(file.label, file.lab_list);
			if (file.fd_cor)
				close(file.fd_cor);
			if (file.fd != -1)
				close(file.fd);
			free((void *)file.hd);
			free((void *)file.cor);
		}
	}
	return (EXIT_SUCCESS);
}
