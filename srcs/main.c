/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:59:23 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/07 15:18:47 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>

int		main(int argc, char **argv)
{
	t_file	file;
	unsigned int	i;

	i = -1;
	if (argc < 2)
		ft_print_asm_usage();
	else
	{
		if (check_extension(argv[argc - 1]) == EXIT_SUCCESS)
		{
			file.fd_cor = 0;
			if (s_to_cor(argv[argc - 1], &file) == EXIT_SUCCESS)
			{
				if (write_to_cor_file(&file) != EXIT_SUCCESS)
					return (EXIT_ERROR);
				ft_dprintf(1, "writing output program to %s\n", file.cor);
				free_file(&file);
				return (EXIT_SUCCESS);
			}
			free_file(&file);
		}		
	}
	return (EXIT_ERROR);
}
