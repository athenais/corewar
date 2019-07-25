#include <asm_errors.h>
#include <asm.h>
#include <stdio.h>

void        deactivate_flag(t_label **label)
{
    t_label *tmp;

    tmp = *label;
    while (tmp)
    {
        if (tmp->flag == active)
        {
            tmp->flag = inactive;
            return ;
        }
        tmp = tmp->next;
    }
    return;
}

t_label     *make_label(char *word)
{
    t_label *new;
    int     size;

    size = ft_strlen(word);
    new = malloc(sizeof(t_label));
    if (!(new->name = malloc(size)))
        return (NULL);
    ft_strcpy(new->name, word);
    new->flag = active;
    new->next = NULL;
    return (new);
}

void    print_dic(t_label *label)
{
    t_label *tmp;

    tmp = label;
    while (tmp)
    {
        printf("|%s| && active = %d\n", tmp->name, tmp->flag);
        tmp = tmp->next;
    }
    printf("\n");
}

int     get_label(t_file *file, char **wd, char *ptr, char **end)
{
    t_label    *tmp;
    t_label    *new;

    if (!(new = make_label(*wd)))
        return (EXIT_ERROR);
//check valid chars
//what if existing label:, diff inst.??
    deactivate_flag(&(file->label));
    *end = (*end != ptr) ? *end + 1 : *end;
    if (file->label == NULL)
        file->label = new;
    else
    {
        tmp = file->label;
        while (tmp->next)
        {
            if (!(ft_strcmp(*wd, tmp->name)) && (tmp->flag = active))
                return (EXIT_SUCCESS);
            tmp = tmp->next;
        }
        tmp->next = new;
    }
  //  print_dic(file->label);
    return (EXIT_SUCCESS);
}
