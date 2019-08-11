/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 14:00:30 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/11 14:59:06 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>
#include <stdio.h>

int			write_inst_with_ocp(t_file *file, t_inst inst)
{
	int		tmp;
	int		shift;
	int		type;
	int		arg;

	shift = c - 2;
	arg = -1;
	file->hd->prog_size += write_to_cor(inst.ocp, c, file);
	while (++arg < file->op_tab[inst.index].arg)
	{
		tmp = inst.ocp >> shift & 0x03;
		if (tmp == T_REG)
			type = c;
		else if (tmp == T_DIR)
			type = (file->op_tab[inst.index].dir_size) ? shrt : i;
		else if (tmp == (T_IND - 1))
			type = shrt;
		else
			return (EXIT_ERROR);
		file->hd->prog_size += write_to_cor(inst.param[arg], type, file);
		shift -= 2;
	}
	return (EXIT_SUCCESS);
}

int			write_instruction(t_file *file, t_inst inst)
{
	int		type;
	int		op_code;

	op_code = file->op_tab[inst.index].op_code;
	file->hd->prog_size += write_to_cor(op_code, c, file);
	if (file->op_tab[inst.index].ocp)
	{
		if (write_inst_with_ocp(file, inst) == EXIT_ERROR)
			return (EXIT_ERROR);
	}
	else
	{
		type = (file->op_tab[inst.index].dir_size) ? shrt : i;
		file->hd->prog_size += write_to_cor(inst.param[0], type, file);
	}
	return (EXIT_SUCCESS);
}
