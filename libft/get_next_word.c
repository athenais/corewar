#include <libft.h>

int						get_next_word(char const *str, char **start, char **end)
{
	char				*ptr;

	ptr = (char *)str;
	while (*ptr && ft_iswhitespace(*ptr))
				ptr++;
	*start = ptr;
	while (*ptr && !ft_iswhitespace(*ptr))
		ptr++;
    *ptr = '\0';
	*end = ptr;
	return ((int)(*end - *start));
}