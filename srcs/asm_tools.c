/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:57:18 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 16:34:55 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <limits.h>
#include <asm.h>

int         valid_instruction_format(char *str, int type)
{
    while (*str && *str != '#')
    {
        if ((*str >= 'a' && *str <= 'z') || *str == '_'
            || (type != label && *str == '-' ))
            str++;
        else if (*str >= '0' && *str <= '9')
            str++;
        else if (*str == LABEL_CHAR)
            str++;
        else if (*str == DIRECT_CHAR)
            str++;
        else if (type == instruction && *str == SEPARATOR_CHAR)
            str++;
        else
            return (EXIT_ERROR);
    }
    return (EXIT_SUCCESS);
}

int     ft_trim(char *split, char **s, int arg)
{
    char    *str;
    int     size;
	int		word_size;

    str = split;
    while (*str && ft_iswhitespace(*str))
        str++;
	size = (int)(str - split);
	*s = str;	
    while (*str && *str != '#' && !(ft_iswhitespace(*str))) 
        str++;
  	word_size = (int)(str - *s);
	size += word_size;
	*s = ft_strndup(*s, word_size);
    while (arg && (ft_iswhitespace(*str)))
    {
        size++;
        str++;
    }
    if (arg)
        return (size + 1);
    return (size);        
}

int64_t     asm_atoi(char **string, int shrt)
{
    int			neg;		
    int64_t		nb;
	uint64_t 	max;

	nb = 0;
	max = 0;
    neg = (**string == '-') ? 1 : 0;
    if (neg)
        (*string)++;
    while (**string >= '0' && **string <= '9')
	{
		max = max * 10 + **string - 48;                    
        nb = nb * 10 + *(*string)++ - 48;
		if (max > LONG_MAX)
			return ((neg) ? 0 : UINT_MAX);
		while ((shrt && nb > USHRT_MAX) || (!shrt && nb > UINT_MAX))
			nb = (shrt) ? nb - USHRT_MAX - 1 : nb - UINT_MAX - 1;
    }
    if (neg)
        nb = (shrt) ? USHRT_MAX - (nb - 1) : UINT_MAX - (nb - 1);
    return (nb);
}

int			inc_size(t_inst *inst, int type)
{
	if (type == T_REG)
	{
		inst->oct = c;
		return (1);
	}
	else if (type == T_IND)
	{
		inst->oct = shrt;
		return (2);
	}
	else
	{
		inst->oct = (inst->dir_size) ? shrt : i;
		return ((inst->dir_size) ? 2 : 4);
	}	
}

void		init_inst(t_inst *inst, t_file *file)
{
	inst->ocp = 0;
	inst->dir_size = file->op_tab[inst->index].dir_size;
	if (file->op_tab[inst->index].ocp)
		inst->wr_size = file->hd->prog_size + 2;
	else
		inst->wr_size = file->hd->prog_size + 1;
}
