/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 18:44:47 by abrunet           #+#    #+#             */
/*   Updated: 2019/09/11 15:07:00 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ERRORS_H
# define ASM_ERRORS_H

# include <errno.h>

# define EXIT_ERROR			-1

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS		0
# endif

# define BUF_SIZE			5

# define BADOP				"Unknown instruction"

# define FILERR				"Invalid file"
# define BADFMT				"Unknown file extension"

# define LNAME              "Champion name size is not valid (> 128)"
# define LCMNT              "Header comment size is not valid (> 2048)"

# define BADNAME            "Name format is not valid"
# define BADCMNT            "Comment format is not valid"

# define NOOP               "File has no instructions"
# define BADOPARG           "Wrong number of arguments for this instruction"
# define OPFMT              "Bad instruction argument"
# define INVLDCHAR          "Invalid character(s)"

# define ERRLAB             "Invalid label format"
# define ERRLABEL           "Label is unknown"
# define DUPLAB             "Label already exists"

# define BADPARAM           "Argument type for instruction is not valid"
# define BADOPTION			"Illegal option -- "
# define BADOPT				"Invalid option value"

# define CHAMPSIZERR		"Bad champion size (either zero or too large)"

# define HELPMSG			"Try 'asm --help' for more information"

void						ft_print_asm_usage(void);
int							ft_puterror(char const *str);
int							ft_puterror_and_close_fd(char const *str, int fd);

#endif
