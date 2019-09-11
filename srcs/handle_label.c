/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:58:14 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 22:12:44 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>

t_label		*new_label(char *word, unsigned int start)
{
	t_label	*new;
	int		size;

	size = 0;
	while (word[size] != ':')
		size++;
	if (!size)
	{
		ft_puterror(ERRLAB, start);
		return (NULL);
	}
	new = malloc(sizeof(t_label));
	if (!(new->name = ft_strnew(size)))
		return (NULL);
	ft_strncpy(new->name, word, size);
	new->start = start;
	new->next = NULL;
	if (valid_instruction_format(new->name, label) != EXIT_SUCCESS)
	{
		ft_puterror(OPFMT, start);
		return (NULL);
	}
	return (new);
}

t_lab		*new_lab(char *wd, unsigned int strt, unsigned int fill, int oct)
{
	t_lab	*new;
	int		size;

	size = ft_strlen(wd);
	new = malloc(sizeof(t_lab));
	if (!(new->name = malloc(size + 1)))
		return (NULL);
	ft_strcpy(new->name, wd);
	new->start = strt;
	new->filler = fill;
	new->size = oct;
	new->next = NULL;
	return (new);
}

t_lab		*lab_list(char **str, t_file *file, t_inst *inst)
{
	t_lab	*tmp;
	t_lab	*new;

	if (!(new = new_lab(*str, file->hd->prog_size, inst->wr_size, inst->oct)))
		return (NULL);
	if (file->lab_list == NULL)
		file->lab_list = new;
	else
	{
		tmp = file->lab_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_label		*make_label(char **wd, t_file *file, unsigned int start)
{
	t_label		*tmp;
	t_label		*new;

	if (!(new = new_label(*wd, start)))
		return (NULL);
	if (file->label == NULL)
		file->label = new;
	else
	{
		tmp = file->label;
		while (tmp->next)
		{
			if (!(ft_strcmp(*wd, tmp->name)))
			{
				ft_puterror(DUPLAB, tmp->start);
				return (NULL);
			}
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	return (new);
}

int			get_label(t_file *file, char **wd, char **end)
{
	(void)end;
	if (make_label(wd, file, file->hd->prog_size) == NULL)
		return (EXIT_ERROR);
	return (EXIT_SUCCESS);
}
