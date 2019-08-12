/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:57:18 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/12 15:34:39 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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

int    generate_ocp(int *ocp, t_arg_type type, int *shift)
{
    int     tmp;

    tmp = (type == T_IND) ? 3 : type;
    tmp <<= *shift;
    *ocp |= tmp;
    *shift -= 2;
    return (EXIT_SUCCESS);
}

int     ft_trim(char *split, char **s, int arg)
{
    char    *str;
    int     size;
	int		word_size;

	//watch out '#'
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

t_label         *reset_file_read(t_file *file, off_t bytes, __unused char **str, t_label *label)
{
  //  free((void *)*str);
    if (lseek(file->fd, bytes + file->str_len, SEEK_SET) < 0)
        return (NULL);
    return (label);
}
