#include <asm_errors.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <asm.h>

int         valid_instruction_format(char *str, int type)
{
    while (*str && *str != '#')
    {
        if ((*str >= 'a' && *str <= 'z') || *str == '_'
            || (type != label && *str == '-' ))
            str++;
        else if (*str >= '0' && *str <= '9')
            str++;
        else if (*str == LABEL_CHAR)
            str++;
        else if (*str == DIRECT_CHAR)
            str++;
        else if (type == instruction && *str == SEPARATOR_CHAR)
            str++;
        else
            return (EXIT_ERROR);
    }
    return (EXIT_SUCCESS);
}

void    generate_ocp(int *ocp, t_arg_type type, int *shift)
{
    int     tmp;

    tmp = (type == T_IND) ? 3 : type;
    tmp <<= *shift;
    *ocp |= tmp;
    *shift -= 2;
}

int     ft_trim(char *split, char **s, int arg)
{
    char    *str;
    int     size;
	int		word_size;

	//watch out '#'
    str = split;
    while (*str && ft_iswhitespace(*str))
        str++;
	size = (int)(str - split);
	*s = str;	
    while (*str && *str != '#' && !(ft_iswhitespace(*str))) 
        str++;
  	word_size = (int)(str - *s);
	size += word_size;
	*s = ft_strndup(*s, word_size);
    while (arg && (ft_iswhitespace(*str)))
    {
        size++;
        str++;
    }
    if (arg)
        return (size + 1);
    return (size);        
}


t_label         *reset_file_read(t_file *file, off_t bytes, __unused char **str, t_label *label)
{
  //  free((void *)*str);
    if (lseek(file->fd, bytes + file->str_len, SEEK_SET) < 0)
        return (NULL);
    return (label);
}
