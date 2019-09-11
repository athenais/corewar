/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:04:27 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 15:04:33 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <unistd.h>
#include <limits.h>
#include <asm_errors.h>

t_label		*label_exist(char *str, t_file *file)
{
	t_label	*tmp;
	int		nb;

	tmp = file->label;
	while (tmp)
	{
		if (ft_strlen(str + 1) == ft_strlen(tmp->name))
		{
			if (!(nb = ft_strcmp(tmp->name, str + 1)))
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

int			parse_lab_list(t_file *file)
{
	t_lab	*tmp;
	t_label	*label;

	file->wr = 1;
	if (!(file->lab_list))
		return (EXIT_SUCCESS);
	tmp = file->lab_list;
	while (tmp)
	{
		label = label_exist(tmp->name, file);
		write_label(file, tmp, label);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
