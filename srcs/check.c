/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 14:01:28 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 19:11:43 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>

int			check_extension(char *str)
{
	char *ptr;

	if ((ptr = ft_strrchr(str, '.')))
	{
		if (!(ft_strcmp(ptr, ASM_EXT)))
			return (EXIT_SUCCESS);
		return (ft_puterror(BADFMT));
	}
	return (ft_puterror(FILERR));
}

int			err_check(char **split)
{
	free_split(split);
	return (EXIT_ERROR);
}

int			check_arg_num(char **split, int arg)
{
	char	*str;
	int		i;

	i = 0;
	while (split[i])
	{
		str = split[i];
		while (*str++)
		{
			if (*str == '#' || *str == ';')
			{
				if (arg != i + 1)
					return (err_check(split));
				return (EXIT_SUCCESS);
			}
		}
		i++;
	}
	if (arg != i)
		return (err_check(split));
	return (EXIT_SUCCESS);
}
