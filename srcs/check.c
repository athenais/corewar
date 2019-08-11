/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 14:01:28 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/11 14:03:04 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm_errors.h>
#include <asm.h>

int		check_extension(char *str)
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
