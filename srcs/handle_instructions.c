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

//make it work for label vv
//check for 32 bits
int         valid_values(char *str, int direct, t_file *file)
{
    int64_t     nb;
    t_label     *label;
    char        *tmp;

    if (*str == 'r')
    {
        if (direct)
            return (EXIT_ERROR);
        tmp = str + 1;
        if ((nb = ft_atoi_parsing(&tmp)) < 0 || nb > REG_NUMBER)
            return (EXIT_ERROR);
    }
    else if (*str == ':')
    {
        if ((label = label_exist(str, file)) == NULL)
        {
            printf("%s = label\n", str);
            if ((label = parse_file_label(str, file, file->bytes)) == NULL)
                return (ft_puterror(ERRLABEL)); 
            else
            {
                printf("yeah!\n");
            }
            
        }
        return (EXIT_SUCCESS);
    }
    else
        nb = ft_atoi_parsing(&str);
 //   printf("nb = %d \n", nb);
    return (EXIT_SUCCESS);        
}

int         handle_instruction(t_file *file, char **str, int index)
{
    char    **split;
    int     arg;
//add valid inst
    arg = file->op_tab[index].arg;
    split = ft_strsplit(*str, ',');
    while (arg-- && *split)
    {
        *str += ft_trim(&(*split), arg);
        if (valid_instruction_format(*split, instruction) != EXIT_SUCCESS)
            return (ft_puterror(OPFMT));
        if (**split != DIRECT_CHAR)
        {
            if (valid_values(*split, 0, file) == EXIT_ERROR)
                return(ft_puterror(OPFMT));
        }
        else if (valid_values((*split + 1), 1, file) == EXIT_ERROR)
            return(ft_puterror(OPFMT));
        split++;
    }
    return (EXIT_SUCCESS);
}

int         get_instruction(t_file *file, char **wd, char *ptr, char **end)
{
    int     index;

    if ((index = is_instruction(*wd, file->op_tab)) < 0)
        return (ft_puterror(OPFMT));
    *end = (*end != ptr) ? *end + 1 : *end;
    if (handle_instruction(file, end, index) != EXIT_SUCCESS)
        return (EXIT_FAILURE);
    //write to file code;
    return (EXIT_SUCCESS);
}
