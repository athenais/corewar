#ifndef ASM_ERRORS_H
# define ASM_ERRORS_H

# include <errno.h>

# define EXIT_ERROR			-1

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS		0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE		1
# endif

# define STDERR_FILENO		2

# define BUF_SIZE			5

# define BADOP				"Unknown instruction"

# define FILERR				"Unsupported file type"
# define BADFMT				"Unknown file extension"

# define LNAME              "Champion name size is too big"
# define LCMNT              "Header comment size is too big"

# define OPFMT              "Bad instruction argument"
# define INVLDCHAR          "Invalid characters"

# define ERRLABEL           "Label is unknown"

# define BADOPTION			"Illegal option -- "
# define BADOPT				"Invalid option value"
# define NULLOPT			"Couldn't find option value"

# define METAERR			"Error while reading metadata"
# define NOCHAMP			"No warrior was loaded in the arena"
# define CHAMPSIZERR		"Bad champion size (either zero or too large)"

# define HELPMSG			"Try 'asm --help' for more information"

void						ft_print_asm_usage(void);
int							ft_puterror(char const *str);
int							ft_puterror_and_close_fd(char const *str, int fd);

#endif
