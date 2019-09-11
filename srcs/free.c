/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:22:13 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 19:26:29 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <unistd.h>
#include <asm_errors.h>

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

int			file_read_free(char *buff, char *str, int err)
{
	free((void *)buff);
	free((void *)str);
	return ((err) ? EXIT_ERROR : EXIT_SUCCESS);
}

void		free_file(t_file *file)
{
	if (file->fd < 0)
		return ;
	free_label(file->label, file->lab_list);
	if (file->fd_cor != -1)
		close(file->fd_cor);
	if (file->fd != -1)
		close(file->fd);
	if (file->tmp)
		free(file->tmp);
	free((void *)file->hd);
	free((void *)file->cor);
	free((void *)file->wr_buff);
}
