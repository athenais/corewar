/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:57:35 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 16:41:49 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
            ft_strncpy(file->hd->prog_name, *end + 1, size);
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
            ft_strncpy(file->hd->comment, *end + 1, size);
            *end = p + 1;
            return (EXIT_SUCCESS);
        }
    }
    return (EXIT_ERROR);
}
