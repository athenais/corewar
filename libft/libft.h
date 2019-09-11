/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:36:33 by thflahau          #+#    #+#             */
/*   Updated: 2019/09/11 22:22:13 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

# define BUFF_SIZE	2048

int					ft_strcmp(char const *s1, char const *s2);
int					ft_isdigit(int c);
void				ft_fast_bzero(void *st, size_t size);
int					ft_printable(int c);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
void				ft_memset(void *s, int c, size_t n);
void				ft_putchar(int c);
void				ft_memcpy(void *dst, void const *src, size_t n);
void				ft_putnstr(char const *s, uint8_t n);
void				ft_putstr_endl(char const *s);
void				ft_putstr_endl_free(char const *s);
void				ft_putstr(char const *s);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(const char *str, int c);
size_t				ft_strlen(char const *str) __attribute__((always_inline));
char				*ft_strndup(char const *s, size_t n);
char				*ft_strnew(size_t n);
char				*ft_strcat(char *s1, char const *s2);
char				*ft_strdup(char const *s);
char				*ft_strsub(char const *s, size_t i, size_t n);
char				*ft_strnjoinfree(char const *s, char const *p, size_t n);
int					ft_readline(int fd, char **string, char **line);
int64_t				ft_atoi_parsing(char **string);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char const *s, int fd);
char				*ft_strncpy(char *dst, char const *src, size_t len);
char				*ft_strcpy(char *dst, char const *src);
int					ft_iswhitespace(char c);
int					get_next_word(char const *str, char **start, char **end);
char				**ft_strsplit(char const *s, char c);
void				ft_dprintf(int fd, char const *fmt, ...);
int					digit_string(char *s);
char				*ft_itoa(int n);

#endif
