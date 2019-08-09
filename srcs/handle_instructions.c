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
int         valid_register(char *str)
{
    char    *tmp;
    int64_t nb;

    tmp = str + 1;
    if ((nb = ft_atoi_parsing(&tmp)) < 0 || nb > 99)
        return (EXIT_ERROR);
    return (EXIT_SUCCESS);
}

int         valid_values(char *str, __unused int direct, t_file *file)
{
    int64_t     nb;
    t_label     *label;

    if (*str == ':')
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

int         handle_instruction(t_file *file, char **str, int index, int *ocp)
{
    char    **split;
    int     arg;
    int     shift;

    shift = c - 2;
 //   unsigned char test1;
//add valid inst
    arg = file->op_tab[index].arg;
    split = ft_strsplit(*str, ',');
    while (arg-- && *split)
    {
        *str += ft_trim(&(*split), arg);
        if (valid_instruction_format(*split, instruction) != EXIT_SUCCESS)
            return (ft_puterror(OPFMT));
        if (**split == 'r' && valid_register(*split) == EXIT_SUCCESS)
        {
            generate_ocp(ocp, T_REG, &shift);
        }
        else if (**split != DIRECT_CHAR)
        {            
            if (valid_values(*split, 0, file) == EXIT_ERROR)
                return(ft_puterror(OPFMT));
             generate_ocp(ocp, T_IND, &shift);
        }
        else
        {
            if (valid_values((*split + 1), 1, file) == EXIT_ERROR)
                return(ft_puterror(OPFMT));
            generate_ocp(ocp, T_DIR, &shift);    
        }   
        split++;
    }
    return (EXIT_SUCCESS);
}

int         get_instruction(t_file *file, char **wd, char *ptr, char **end)
{
    int     index;
    int     ocp;

    ocp = 0;
    if ((index = is_instruction(*wd, file->op_tab)) < 0)
        return (ft_puterror(OPFMT));
    else
        write_to_cor(file->op_tab[index].op_code, c, file);
    *end = (*end != ptr) ? *end + 1 : *end;
    if (handle_instruction(file, end, index, &ocp) != EXIT_SUCCESS)
        return (EXIT_FAILURE);
    if (file->op_tab[index].ocp)
        write_to_cor(ocp, c, file);
    //write to file code;
    return (EXIT_SUCCESS);
}
