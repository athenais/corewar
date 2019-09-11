/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:58:49 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 22:37:16 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <asm_errors.h>

void				ft_print_asm_usage(void)
{
	ft_dprintf(1, "usage: ./asm <file.s>\n");
}

int					ft_puterror(char const *string, int line)
{
	char			*str;

	if (string != NULL)
	{
		str = ft_itoa(line);
		ft_dprintf(1, "asm: %s -- ", string);
		ft_dprintf(1, "line[%s]\n", str);
		if (str)
			free(str);
	}
	else
		ft_dprintf(1, "%s\n", HELPMSG);
	return (EXIT_ERROR);
}
