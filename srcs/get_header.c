#include <asm.h>
#include <asm_errors.h>
#include <stdio.h>
#include <unistd.h>

//watch out for end + 1 (add ptr);
void        write_hd_to_cor(char *str, t_file *file, int size, int len)
{
    if (len == COMMENT_LENGTH)
        write_to_cor(36, i, file);
    while (*str)
    {
        write_to_cor((int)*str, c, file);
        str++;
    }
    while (size < len)
    {
        write_to_cor('\0', c, file);
        size++;
    }
}

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
      //      write_hd_to_cor(file->name, file, size, PROG_NAME_LENGTH);
            return (EXIT_SUCCESS);
        }
    }
    //check endian;
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
      //      file->hd->prog_size = 36;
      //      file->hd->magic = COREWAR_EXEC_MAGIC;
     //       printf("%lu = size\n", sizeof(header_t));
      //      write(file->fd_cor, file->hd, sizeof(header_t));
    //        write_hd_to_cor(file->cmnt, file, size, COMMENT_LENGTH);
            return (EXIT_SUCCESS);
        }
    }
    return (EXIT_ERROR);
}
