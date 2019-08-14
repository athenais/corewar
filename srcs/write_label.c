/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:59:37 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/14 16:57:51 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <asm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <asm_errors.h>

/*void	free_lab(t_lab **lab)
{

}

void	free_label(t_label **label)
{

}*/

int		write_label(t_file *file, t_lab *lab, t_label *label)
{
	unsigned int	diff;
	unsigned short	shrt_sum;
	unsigned int	i_sum;
	unsigned int	off_set;

	off_set = sizeof(header_t) + lab->filler;
	lseek(file->fd_cor, off_set, SEEK_SET);
	diff = 	lab->start - label->start;
	if (lab->size == shrt)
	{
		shrt_sum = USHRT_MAX - (diff - 1);
		printf("%u = short\n", shrt_sum);
		if (write_to_cor(shrt_sum, shrt, file) == EXIT_ERROR)
			return (EXIT_ERROR);
	}
	else
	{
		i_sum = UINT_MAX - (diff - 1);
		printf("%u = i\n", i_sum);
		if (write_to_cor(i_sum, i, file) == EXIT_ERROR)
			return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}	

void    print_lst(t_lab *label)
{
    t_lab *tmp;

    tmp = label;
    while (tmp)
    {
        printf("|%s| \n", tmp->name);
        tmp = tmp->next;
    }
    printf("\n");
}

int		parse_lab_list(t_file *file)
{
	t_lab	*tmp;
	t_label	*label;

	if (!(file->lab_list))
	{
		//free label
		return (EXIT_SUCCESS);
	}
	print_dic(file->label);
	printf("\n");
	print_lst(file->lab_list);
	tmp = file->lab_list;
	while (tmp)
	{
		if (!(label = label_exist(tmp->name, file)))
		{
			//free label
			//free lab
			return (ft_puterror(ERRLABEL));
		}
		write_label(file, tmp, label);
		tmp = tmp->next;
	}
	//free all
	return (EXIT_SUCCESS);
}