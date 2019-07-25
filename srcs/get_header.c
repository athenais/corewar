#include <asm.h>
#include <asm_errors.h>

int     get_champ_name(t_file *file, __unused char **wd, __unused char *ptr, char **end)
{
    char    *p;
    int     size;

    *end = *end + 1;
    while ((ft_iswhitespace(**end)))
        (*end)++;
    if (**end == '"')
    {
        if ((p = ft_strchr(*end + 1, '"' )))
        { 
            if ((size = (int)(p - (*end + 1))) > PROG_NAME_LENGTH)
                return (ft_puterror(LNAME));
            ft_strncpy(file->name, *end + 1, size);
            *end = p + 1;
            return (EXIT_SUCCESS);
        }
    }
    return (EXIT_ERROR);
}

int     get_comment(t_file *file, __unused char **wd, __unused char *ptr, char **end)
{
    char    *p;
    int     size;

    *end = *end + 1;
    while ((ft_iswhitespace(**end)))
        (*end)++;
    if (**end == '"')
    {
        if ((p = ft_strchr(*end + 1, '"' )))
        {
            if ((size = (int)(p - (*end + 1))) > COMMENT_LENGTH)
                return (ft_puterror(LCMNT));
            ft_strncpy(file->cmnt, *end + 1, size);
            *end = p + 1;
            return (EXIT_SUCCESS);
        }
    }
    return (EXIT_ERROR);
}
