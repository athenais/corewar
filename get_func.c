#include <stdio.h>
#include <asm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include <asm_errors.h>

uint8_t     get_champ_name(t_file *file, __unused char *wd, char *ptr, char *end)
{
    char    *p;
    int     size;

    if (end != ptr)
    {
        end = end + 1;
        while ((ft_iswhitespace(*end)))
            end++;
        if (*end == '"')
        {
            if ((p = ft_strchr(end + 1, '"' )))
            {
                if ((size = (int)(p - (end + 1))) > PROG_NAME_LENGTH)
                    return (EXIT_ERROR);
                ft_strncpy(file->name, end + 1, size);
                return (EXIT_SUCCESS);
            }
        }
    }
    return (EXIT_ERROR);
}

uint8_t     get_comment(t_file *file, __unused char *wd, char *ptr, char *end)
{
    char    *p;
    int     size;

    if (end != ptr)
    {
        end = end + 1;
        while ((ft_iswhitespace(*end)))
            end++;
        if (*end == '"')
        {
            if ((p = ft_strchr(end + 1, '"' )))
            {
                if ((size = (int)(p - (end + 1))) > COMMENT_LENGTH)
                    return (EXIT_ERROR);
                ft_strncpy(file->cmnt, end + 1, size);
                return (EXIT_SUCCESS);
            }
        }
    }
    return (EXIT_ERROR);
}