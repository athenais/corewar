/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:59:37 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 19:05:46 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <unistd.h>
#include <limits.h>
#include <asm_errors.h>

t_label		*label_exist(char *str, t_file *file)
{
	t_label	*tmp;

	tmp = file->label;
	while (tmp)
	{
		if (ft_strlen(str) == ft_strlen(tmp->name))
		{
			if (ft_strcmp(tmp->name, str + 1) == 58)
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int			write_label(t_file *file, t_lab *lab, t_label *label)
{
	unsigned int	diff;
	unsigned short	shrt_sum;
	unsigned int	i_sum;
	unsigned int	off_set;

	off_set = sizeof(t_header) + lab->filler;
	lseek(file->fd_cor, off_set, SEEK_SET);
	diff = lab->start - label->start;
	if (lab->size == shrt)
	{
		shrt_sum = USHRT_MAX - (diff - 1);
		if (write_to_cor(shrt_sum, shrt, file) == EXIT_ERROR)
			return (EXIT_ERROR);
	}
	else
	{
		i_sum = UINT_MAX - (diff - 1);
		if (write_to_cor(i_sum, i, file) == EXIT_ERROR)
			return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

/*
** add free
*/

int			parse_lab_list(t_file *file)
{
	t_lab	*tmp;
	t_label	*label;

	if (!(file->lab_list))
		return (EXIT_SUCCESS);
	tmp = file->lab_list;
	while (tmp)
	{
		if (!(label = label_exist(tmp->name, file)))
			return (ft_puterror(ERRLABEL));
		write_label(file, tmp, label);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
