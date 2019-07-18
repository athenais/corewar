#include <stdio.h>
#include <asm_errors.h>
#include <asm.h>
#include "libft/libft.h"

int		check_extension(char *str)
{
	char *ptr;

	if ((ptr = ft_strrchr(str, '.')))
	{
		if (!(ft_strcmp(ptr, ASM_EXT)))
			return (EXIT_SUCCESS);
		else
			ft_puterror(BADFMT);
	}
	else
		ft_puterror(FILERR);
	return (EXIT_FAILURE);
}		
