#include <asm_errors.h>
#include <asm.h>
#include <unistd.h>

int		main(int argc, char **argv)
{
	t_file	file;

	if (argc < 2)
		ft_print_asm_usage();
	else
	{
		if (check_extension(argv[argc - 1]) == EXIT_SUCCESS)
		{
			if (s_to_cor(argv[argc - 1], &file) == EXIT_SUCCESS)
			{
				lseek(file.fd_cor, 0, SEEK_SET);
				write_header(&file);			
			}
			free((void *)file.hd);
			free((void *)file.cor);
		}
	}
	return (0);
}
