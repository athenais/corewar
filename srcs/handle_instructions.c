/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:57:44 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/11 14:36:49 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>
#include <stdio.h>

/*
** make it work for label vv
**check for 32 bits
*/

int			valid_register(char *str, t_inst *inst, int i)
{
	char	*tmp;
	int64_t	nb;

	tmp = str + 1;
	if ((nb = ft_atoi_parsing(&tmp)) < 0 || nb > 99)
		return (EXIT_ERROR);
	inst->param[i] = nb;
	return (EXIT_SUCCESS);
}

int			valid_values(char *str, t_file *file, t_inst *inst, int i)
{
	int64_t		nb;
	t_label		*label;

	if (*str == ':')
	{
		if ((label = label_exist(str, file)) == NULL)
		{
			printf("yeah!\n");
		}
		inst->param[i] = 0;
		return (EXIT_SUCCESS);
	}
	else
	{
		nb = ft_atoi_parsing(&str);
		inst->param[i] = nb;
	}
	return (EXIT_SUCCESS);
}

int			check_param(t_file *file, char *s, t_inst *inst, int i)
{
	static int		shift;

	if (!i)
		shift = c - 2;
	if (valid_instruction_format(s, instruction) != EXIT_SUCCESS)
		return (ft_puterror(OPFMT));
	if (*s == 'r' && valid_register(s, inst, i) == EXIT_SUCCESS)
	{
		generate_ocp(&inst->ocp, T_REG, &shift);
	}
	else if (*s != DIRECT_CHAR)
	{
		if (valid_values(s, file, inst, i) == EXIT_ERROR)
			return (ft_puterror(OPFMT));
		generate_ocp(&inst->ocp, T_IND, &shift);
	}
	else
	{
		if (valid_values((s + 1), file, inst, i) == EXIT_ERROR)
			return (ft_puterror(OPFMT));
		generate_ocp(&inst->ocp, T_DIR, &shift);
	}
	free((void *)s);
	return (EXIT_SUCCESS);
}

int			handle_instruction(t_file *file, char **str, t_inst *inst)
{
	char	**split;
	char	*s;
	int		arg;
	int		i;

	s = NULL;
	arg = file->op_tab[inst->index].arg;
	split = ft_strsplit(*str, ',');
	i = -1;
	while (arg-- && i++ < file->op_tab[inst->index].arg)
	{
		*str += ft_trim(split[i], &s, arg);
		if (check_param(file, s, inst, i) == EXIT_ERROR)
			return (EXIT_ERROR);
	}
	free_split(split);
	return (EXIT_SUCCESS);
}

int			get_instruction(t_file *file, char **wd, char *ptr, char **end)
{
	t_inst	inst;

	inst.ocp = 0;
	if ((inst.index = is_instruction(*wd, file->op_tab)) < 0)
		return (ft_puterror(OPFMT));
	*end = (*end != ptr) ? *end + 1 : *end;
	if (handle_instruction(file, end, &inst) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	write_instruction(file, inst);
	return (EXIT_SUCCESS);
}
