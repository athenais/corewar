/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:18:39 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 17:10:28 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <asm_errors.h>

int			generate_ocp(int *ocp, t_arg_type type, int *shift)
{
	int		tmp;

	tmp = (type == T_IND) ? 3 : type;
	tmp <<= *shift;
	*ocp |= tmp;
	*shift -= 2;
	return (EXIT_SUCCESS);
}

char		*ft_itoa_bse(unsigned int n, int base, int len)
{
	char	*new;
	char	*base_key;

	base_key = "0123456789abcdef";
	if (!(new = ft_strnew(len)))
		return (NULL);
	len--;
	while (len >= 0)
	{
		new[len] = base_key[n % base];
		n /= base;
		len--;
	}
	return (new);
}
