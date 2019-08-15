/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:57:44 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 18:24:34 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <limits.h>
#include <asm.h>

int			valid_register(char *str, t_inst *inst, int i)
{
	char	*tmp;
	int64_t	nb;

	tmp = str + 1;
	if (ft_strlen(tmp) > 2 || !(digit_string(tmp)))
		return (EXIT_ERROR);
	if ((nb = ft_atoi_parsing(&tmp)) < 0 || nb > 99)
		return (EXIT_ERROR);
	inst->param[i] = nb;
	return (EXIT_SUCCESS);
}

int			valid_values(char *str, t_file *file, t_inst *inst, int i)
{
	int			shrt;
	int			direct;
	char		*tmp;

	direct = (*str != DIRECT_CHAR) ? 0 : 1;
	tmp = (direct) ? str + 1 : str;
	if (*tmp == ':')
	{
		if (!(lab_list(&tmp, file, inst)))
			return (EXIT_ERROR);
		inst->param[i] = 0;
		return (EXIT_SUCCESS);
	}
	if (!(digit_string(tmp)))
		return (EXIT_ERROR);
	shrt = ((direct && inst->dir_size) || !direct) ? 1 : 0;
	inst->param[i] = asm_atoi(&tmp, shrt);
	return (EXIT_SUCCESS);
}

int			check_param(t_file *file, char *s, t_inst *inst, int i)
{
	static int		shift;
	int				type;

	if (!i)
		shift = c - 2;
	if (valid_instruction_format(s, instruction) != EXIT_SUCCESS)
		return (ft_puterror(OPFMT));
	if (*s == 'r')
	{
		inc_size(inst, T_REG);
		if (valid_register(s, inst, i) == EXIT_SUCCESS
			&& (inst->wr_size += inc_size(inst, T_REG)))
			return (generate_ocp(&inst->ocp, T_REG, &shift));
	}
	else
	{
		type = (*s != DIRECT_CHAR) ? T_IND : T_DIR;
		inc_size(inst, type);
		if (valid_values(s, file, inst, i) == EXIT_SUCCESS
			&& (inst->wr_size += inc_size(inst, type)))
			return (generate_ocp(&inst->ocp, type, &shift));
	}
	return (ft_puterror(OPFMT));
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
		{
			free_split(split);
			free((void *)s);
			return (EXIT_ERROR);
		}
		free((void *)s);
	}
	free_split(split);
	return (EXIT_SUCCESS);
}

int			get_instruction(t_file *file, char **wd, char *ptr, char **end)
{
	t_inst	inst;

	if ((inst.index = is_instruction(*wd, file->op_tab)) < 0)
		return (ft_puterror(BADOP));
	init_inst(&inst, file);
	*end = (*end != ptr) ? *end + 1 : *end;
	if (handle_instruction(file, end, &inst) != EXIT_SUCCESS)
		return (EXIT_ERROR);
	if (write_instruction(file, inst) == EXIT_ERROR)
		return (EXIT_ERROR);
	if (file->hd->prog_size > UCHAR_MAX)
		return (ft_puterror(CHAMPSIZERR));
	return (EXIT_SUCCESS);
}
