/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:22:13 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/09 19:29:39 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <unistd.h>

void		free_label(t_label *label, t_lab *lab)
{
	void	*tmp;

	if (label)
	{
		tmp = label;
		while (label)
		{
			tmp = label;
			free(label->name);
			label = label->next;
			free(tmp);
		}
	}
	if (lab)
	{
		tmp = lab;
		while (lab)
		{
			tmp = lab;
			free(lab->name);
			lab = lab->next;
			free(tmp);
		}
	}
}

void		free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
}

void		free_file(t_file *file)
{
	free_label(file->label, file->lab_list);
	if (file->fd_cor)
		close(file->fd_cor);
	if (file->fd != -1)
		close(file->fd);
	free((void *)file->hd);
	free((void *)file->cor);
	free((void *)file->wr_buff);
}
