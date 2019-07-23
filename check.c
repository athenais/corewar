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
		return (ft_puterror(BADFMT));
	}
	return (ft_puterror(FILERR));
}		
