#include <asm_errors.h>
#include <asm.h>

int		main(int argc, char **argv)
{
	
	if (argc < 2)
		ft_print_asm_usage();
	else
	{
		if (check_extension(argv[argc - 1]) == EXIT_SUCCESS)
			s_to_cor(argv[argc - 1]);			
	}
	return (0);
}
