# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/10 18:37:35 by thflahau          #+#    #+#              #
#    Updated: 2019/08/15 18:31:28 by abrunet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

INCLUDE	=	./

CFLAGS	=	-Wall -Wextra -Werror -I $(INCLUDE) -c

NAME	=	libft.a

SRCS	=	ft_isdigit.c	ft_memset.c		ft_putchar.c			\
			ft_putnstr.c	ft_putstr.c 	ft_putstr_endl.c		\
			ft_strnew.c 	ft_strlen.c		ft_strnjoinfree.c 		\
			ft_fast_bzero.c	ft_strrchr.c 	ft_atoi_parsing.c 		\
			ft_strdup.c 	ft_strndup.c	ft_strchr.c				\
			ft_strsub.c		ft_strcmp.c		ft_strncmp.c 			\
			ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c			\
			ft_memcpy.c		ft_readline.c	ft_strcat.c				\
			ft_strcpy.c		ft_strncpy.c	ft_putstr_endl_free.c	\
			get_next_word.c	ft_strsplit.c 	ft_dprintf.c	  		\
			digit_string.c	ft_printable.c	ft_iswhitespace.c	

OBJDIR	=	objs/

OBJS	=	$(SRCS:.c=.o)

OBJDIR1	=	$(addprefix $(OBJDIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS)
	ar -cq $@ $(OBJS)
	ranlib $@

%.o: %.c	libft.h
	@gcc $(CFLAGS) -o $@ -c $<

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.SILENT: all clean fclean $(NAME)
.phony: $(NAME) clean fclean re
