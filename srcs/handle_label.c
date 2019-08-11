/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:58:14 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/11 13:58:17 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_label     *new_label(char *word)
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

t_label     *label_exist(char *str, t_file *file)
{
    t_label     *tmp;
 
    tmp = file->label;
    while (tmp)
    {
        if (ft_strlen(str) == ft_strlen(tmp->name))
        {
            if (ft_strcmp(tmp->name, str + 1) == 58)
                return (tmp);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

t_label     *make_label(char **wd, t_file *file)
{
    t_label    *tmp;
    t_label    *new;

    if (!(new = new_label(*wd)))
        return (NULL);
    if (file->label == NULL)
        file->label = new;
    else
    {
        tmp = file->label;
        while (tmp->next)
        {
            if (!(ft_strcmp(*wd, tmp->name)) && (tmp->flag = active))
                return (new);
            tmp = tmp->next;
        }
        tmp->next = new;
    }
    return (new);
}

int     get_label(__unused t_file *file, char **wd, char *ptr, char **end)
{
//check valid chars
//what if existing label:, diff inst.??

//    deactivate_flag(&(file->label));
    if (valid_instruction_format(*wd, label) != EXIT_SUCCESS)
        return (ft_puterror(OPFMT));
    *end = (*end != ptr) ? *end + 1 : *end;
//    if (make_label(wd, file) == NULL)
//        return (EXIT_ERROR);
    return (EXIT_SUCCESS);
}
