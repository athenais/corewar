/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tools_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 13:14:15 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 19:04:53 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <asm_errors.h>

int			is_instruction(char *str, t_op const *op_tab)
{
	int		index;

	index = -1;
	while (op_tab[++index].name)
	{
		if (!(ft_strcmp(str, op_tab[index].name)))
			return (index);
	}
	return (EXIT_ERROR);
}

int			get_end_word_index(char **start)
{
	int		i;

	i = 0;
	while ((*start)[i] && !ft_iswhitespace((*start)[i])
		&& (*start)[i] != ':' && (*start)[i] != '%')
		i++;
	return (i);
}
