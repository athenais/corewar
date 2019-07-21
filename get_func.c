#include <asm.h>
#include "libft/libft.h"
#include <asm_errors.h>
#include <stdio.h>

int     get_champ_name(t_file *file, __unused char *wd, char *ptr, char *end)
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

int     get_comment(t_file *file, __unused char *wd, char *ptr, char *end)
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

t_label     *make_label(char *word)
{
    t_label *new;
    int     size;

    size = ft_strlen(word);
    new = malloc(sizeof(t_label));
    if (!(new->name = malloc(size)))
        return (NULL);
    ft_strncpy(new->name, word, size - 1);
    printf("|%s| = new", new->name);
    new->next = NULL;
    return (new);
} 

int     get_label(t_file *file, char *wd, __unused char *ptr, __unused char *end)
{
    t_label    *tmp;
//check valid chars
    if (file->label == NULL)
    {
         if (!(file->label = make_label(wd)))
            return (EXIT_ERROR);
    }
    else
    {
        tmp = file->label;
        while (tmp->next != NULL)
            tmp = tmp->next;
        if (!(tmp = make_label(wd)))
            return (EXIT_ERROR);
    }
    return (EXIT_SUCCESS);
}