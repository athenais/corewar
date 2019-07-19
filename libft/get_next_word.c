#include <libft.h>
#include <stdio.h>

void					get_next_word(char const *str, char **start, char **end)
{
	char				*ptr;

	ptr = (char *)str;
	while (*ptr && ft_iswhitespace(*ptr))
			ptr++;
	*start = ptr;
	while (*ptr && !ft_iswhitespace(*ptr))
		ptr++;
	*end = ptr;
    *ptr = '\0';
}