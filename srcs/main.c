/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:59:23 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 22:09:18 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>

int		valid_test(t_file *file)
{
	int		err;
	t_lab	*tmp;
	t_label	*label;

	err = 0;
	if (file->cmnt == 1)
		err = ft_puterror(BADCMNT, file->line);
	else if (!file->op)
		err = ft_puterror(NOOP, file->line);
	else if (file->lab_list)
	{
		tmp = file->lab_list;
		while (tmp && !err)
		{
			if (!(label = label_exist(tmp->name, file)))
				err = ft_puterror(ERRLABEL, tmp->start);
			tmp = tmp->next;
		}
	}
	if (err)
	{
		free_file(file);
		return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	t_file			file;

	if (argc < 2)
		ft_print_asm_usage();
	else
	{
		if (check_extension(argv[argc - 1]) == EXIT_SUCCESS)
		{
			file.fd_cor = 0;
			if (s_to_cor(argv[argc - 1], &file) == EXIT_SUCCESS)
			{
				if (valid_test(&file) == EXIT_ERROR)
					return (EXIT_ERROR);
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
