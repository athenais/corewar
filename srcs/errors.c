#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <asm_errors.h>

void				ft_print_asm_usage(void)
{
	printf("usage: ./asm <file.s>\n");	
}

int					ft_puterror(char const *string)
{
	if (string != NULL)
		printf("asm: %s\n", string);
	else
		printf("%s\n", HELPMSG);
	return (EXIT_ERROR);
}

int					ft_puterror_and_close_fd(char const *string, int fd)
{
	if (__builtin_expect((close(fd) < 0), 0))
		ft_puterror(strerror(errno));
	return (ft_puterror(string));
}
