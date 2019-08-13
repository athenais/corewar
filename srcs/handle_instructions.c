/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:57:44 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/12 15:34:38 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>
#include <limits.h>
#include <stdio.h>

/*
** make it work for label vv
**check for 32 bits
*/

int			digit_string(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (!(ft_isdigit(s[i])))
		{
			if (s[i] != '-' && i != 0)
				return (0);
		}
	}
	return (1);
}

int64_t     atoi_tst(char **string, int shrt)
{
    int      neg;
    int64_t  nb;

    nb = 0;
    neg = (**string == '-') ? 1 : 0;
    if (neg)
        (*string)++;
    while (**string >= '0' && **string <= '9')
	{
        if ((shrt && nb > USHRT_MAX) || (!shrt && nb > INT_MAX))
            nb = 0;
        nb = nb * 10 + *(*string)++ - 48;
    }
    if (neg)
        nb = (shrt) ? USHRT_MAX - (nb - 1) : INT_MAX - (nb - 1);
    return (nb);
}

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

int			valid_values(char *str, __unused t_file *file, t_inst *inst, int i)
{
	int			shrt;
	int			direct;
	char		*tmp;
//	t_label		*label;

	direct = (*str != DIRECT_CHAR) ? 0 : 1;
	if (*str == ':' || (direct && *(str + 1) == ':'))
	{
		inst->param[i] = 0;
		return (EXIT_SUCCESS);
	}
	tmp = (direct) ? str + 1 : str;
	if (!(digit_string(tmp)))
		return (EXIT_ERROR);
	shrt = ((direct && inst->dir_size) || !direct) ? 1 : 0;
	inst->param[i] = atoi_tst(&tmp, shrt);		
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
		if (valid_register(s, inst, i) == EXIT_SUCCESS)
			return (generate_ocp(&inst->ocp, T_REG, &shift));
	}
	else
	{
		type = (*s != DIRECT_CHAR) ? T_IND : T_DIR;
		if (valid_values(s, file, inst, i) == EXIT_SUCCESS)
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
		printf("%s = split\n", s);
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

	inst.ocp = 0;
	if ((inst.index = is_instruction(*wd, file->op_tab)) < 0)
		return (ft_puterror(BADOP));
	inst.dir_size = file->op_tab[inst.index].dir_size;
	*end = (*end != ptr) ? *end + 1 : *end;
	if (handle_instruction(file, end, &inst) != EXIT_SUCCESS)
		return (EXIT_ERROR);
	if (write_instruction(file, inst) == EXIT_ERROR)
		return (EXIT_ERROR);
	return (EXIT_SUCCESS);
}
