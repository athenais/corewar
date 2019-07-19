#include <asm.h>
#include "libft/libft.h"
#include <asm_errors.h>
#include <stdio.h>

int			is_instruction(char *str, t_op *op_tab)
{
	int		index;

	index = -1;
	while (op_tab[++index].name)
	{
		if (!(ft_strcmp(str, op_tab[index].name)))
			return (index);
	}
	return (EXIT_ERROR);
}

int         valid_instruction_format(int arg, char *str)
{
    int     count;

    count = 1;
    while (*str && *str != '#')
    {
        if (ft_iswhitespace(*str))
            str++; 
        else if ((*str >= 'a' && *str <= 'z') || *str == '_')
            str++;
        else if (*str >= '0' && *str <= '9')
            str++;
        else if (*str == LABEL_CHAR)
            str++;
        else if (*str == DIRECT_CHAR)
            str++;
        else if (*str == SEPARATOR_CHAR)
        {
            str++;
            count += 1;
        }
        else
            return (EXIT_ERROR);
    }
    if (count != arg)
        return (EXIT_ERROR);
    return (EXIT_SUCCESS);
}

void      ft_trim(char **split)
{
    //watch out for free maybe return pointer to split;
    char    *str;

    str = *split;
    while (*str && ft_iswhitespace(*str))
        str++;
    *split = str;
    while (*str && *str != '#' && !(ft_iswhitespace(*str)))
        str++;
    *str = '\0';        
}

int         get_instruction(t_file *file, char *wd, char *ptr, char *end)
{
    int     index;
    char    **split;
    int     arg;

    index = is_instruction(wd, file->op_tab);
    arg = file->op_tab[index].arg;

    if (end != ptr)
    {
        if (valid_instruction_format(arg, end + 1) == EXIT_SUCCESS)
        {
            split = ft_strsplit(end + 1, ',');
            while (arg--)
            {
                ft_trim(&(*split));
                //trim
                //if !%
                //check if r < max
                //else if valeur = num
                //else if label
                split++;
            }
        }
    }
    return (EXIT_ERROR);
}