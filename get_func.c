#include <asm.h>
#include "libft/libft.h"
#include <asm_errors.h>
#include <stdio.h>

int     get_champ_name(t_file *file, char **wd, int ret, char **end)
{
    char    *p;
    int     size;


    if (*end != (*wd + ret))
    {
        *end = *end + 1;
        while ((ft_iswhitespace(**end)))
            (*end)++;
        if (**end == '"')
        {
            if ((p = ft_strchr(*end + 1, '"' )))
            { 
                if ((size = (int)(p - (*end + 1))) > PROG_NAME_LENGTH)
                    return (EXIT_ERROR);
                ft_strncpy(file->name, *end + 1, size);
                *end = p + 1;
                return (EXIT_SUCCESS);
            }
        }
    }
    return (EXIT_ERROR);
}

int     get_comment(t_file *file, char **wd, int ret, char **end)
{
    char    *p;
    int     size;

    if (*end != (*wd + ret))
    {
        *end = *end + 1;
        while ((ft_iswhitespace(**end)))
            (*end)++;
        if (**end == '"')
        {
            if ((p = ft_strchr(*end + 1, '"' )))
            {
                if ((size = (int)(p - (*end + 1))) > COMMENT_LENGTH)
                    return (EXIT_ERROR);
                ft_strncpy(file->cmnt, *end + 1, size);
                *end = p + 1;
                return (EXIT_SUCCESS);
            }
        }
    }
    return (EXIT_ERROR);
}

t_label     *make_label(char *word)
{
    t_label *new;
    int     size;

    size = ft_strlen(word);
    new = malloc(sizeof(t_label));
    if (!(new->name = malloc(size)))
        return (NULL);
    ft_strncpy(new->name, word, size - 1);
    new->next = NULL;
    return (new);
} 

int     get_label(t_file *file, char **wd, __unused int ret, char **end)
{
    t_label    *tmp;
//check valid chars
//what if existing label:, diff inst.??
//add file->flag to 1 if existing;
    *end = *end + 1;
    if (file->label == NULL)
    {
         if (!(file->label = make_label(*wd)))
            return (EXIT_ERROR);
    }
    else
    {
        tmp = file->label;
        while (tmp->next != NULL)
        {
            if (!(ft_strcmp(*wd, tmp->name)))
                return (EXIT_SUCCESS);
            tmp = tmp->next;
        }
        if (!(tmp = make_label(*wd)))
            return (EXIT_ERROR);
    }
    return (EXIT_SUCCESS);
}