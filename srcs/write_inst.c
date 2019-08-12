/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 14:00:30 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/12 12:40:30 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>
#include <stdio.h>


int			valid_param(t_file *file, int index, int param, int arg)
{
	int		type;
	int		sum1;
	int		sum2;
	int		sum3;
	int		sum4;

	sum1 = T_REG + T_IND + T_DIR;
	sum2 = T_REG + T_IND;
	sum3 = T_IND + T_DIR;
	sum4 = T_REG + T_DIR;
	type = file->op_tab[index].type[arg];
	param = (param == IND_CODE) ? T_IND : param ;
	if (type == param || type == sum1)
		return (EXIT_SUCCESS);
	if (param == T_IND && type < param)
		return (EXIT_ERROR);
	if (param == T_DIR && (type != sum3 && type != sum4))
		return (EXIT_ERROR);
	if (param == T_REG && (type != sum2 && type != sum4))
		return (EXIT_ERROR);
	return (EXIT_SUCCESS);
}

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
		if (valid_param(file, inst.index, tmp, arg) == EXIT_ERROR)
			return (ft_puterror(BADPARAM));
		if (tmp == T_REG)
			type = c;
		else if (tmp == T_DIR)
			type = (file->op_tab[inst.index].dir_size) ? shrt : i;
		else if (tmp == IND_CODE)
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
