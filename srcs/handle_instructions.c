#include <asm_errors.h>
#include <asm.h>
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
    //beware '-'
    count = 1;
    while (*str && *str != '#')
    {
        if (ft_iswhitespace(*str))
            str++; 
        else if ((*str >= 'a' && *str <= 'z') || *str == '_' || *str == '-')
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

int     ft_trim(char **split)
{
    //watch out for free maybe return pointer to split;
    char    *str;
    int     cnt;

    cnt = 0;
    str = *split;
    while (*str && ft_iswhitespace(*str))
    {
        str++;
        cnt++;
    }
    *split = str;
    while (*str && *str != '#' && !(ft_iswhitespace(*str)))
    {
        str++;
        cnt++;
    }
    *str = '\0';
    return (cnt + 1);        
}
//check for 32 bits
int         valid_values(char *str, int direct)
{
    int64_t     nb;
    char        *tmp;

    if (*str == 'r')
    {
        if (!direct)
        {
            tmp = str + 1;
            if ((nb = ft_atoi_parsing(&tmp)) < 0 || nb > REG_NUMBER)
                return (EXIT_ERROR);
        }
    }
    else if (*str == ':')
    {
        tmp = str + 1;
            //look for existing label
            //-->get_opcode + write
            //else
            //
            // go through file;
         return (EXIT_SUCCESS);
    }
    else
        nb = ft_atoi_parsing(&str);
 //   printf("nb = %d \n", nb);
    return (EXIT_SUCCESS);        
}

int         get_instruction(t_file *file, char **wd, char *ptr, char **end)
{
    int     index;
    char    **split;
    int     arg;

    if ((index = is_instruction(*wd, file->op_tab)) < 0)
        return (ft_puterror(OPFMT));
    arg = file->op_tab[index].arg;

    if (valid_instruction_format(arg, *end + 1) == EXIT_SUCCESS)
    {
        split = ft_strsplit(*end + 1, ',');
        while (arg--)
        {
            *end += ft_trim(&(*split));
            if (**split != DIRECT_CHAR)
            {
               if (valid_values(*split, 0) == EXIT_ERROR)
                 return(ft_puterror(OPFMT));
            }    
            else if (valid_values((*split + 1), 1) == EXIT_ERROR)
                return(ft_puterror(OPFMT));
            split++;
        }
    }
    *end = (*end != ptr) ? *end + 1 : *end;
    return (EXIT_SUCCESS);
}
