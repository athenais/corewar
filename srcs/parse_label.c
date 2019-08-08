#include <stdio.h>
#include <asm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <asm_errors.h>

t_label             *parse_line_label(char **buff,  char *str, t_file *file)
{
    char    *start;
    char    *end;
    int     size;

    if ((size = get_next_word((char const *)*buff, &start, &end)) > 0)
    {
        if (start[size - 1] == ':' && (ft_strlen(start) == ft_strlen(str)))
        {
            if (ft_strcmp(start, str + 1) == 58)
                return (make_label(&start, file));
        }
    }
    return (NULL);
}

int                find_instruction(char **buff, char *ptr, t_file *file)
{
    char            *start;
    int             index;
    char            *end;
    char            *tmp;

    end = *buff;
    tmp = *buff;
    while (end != ptr)
    {
        if (get_next_word((char const *)tmp, &start, &end) > 0)
        {
            if ((index = is_instruction(start, file->op_tab)) >= 0)
            {
                end = (end != ptr) ? end + 1 : end;
                return (handle_instruction(file, &end, index, 0));
            }
        }
        if (end != ptr)
            tmp = end + 1;
    }
    return (EXIT_ERROR);
}
//write return fd to norm func, pass tmp as arg;
t_label             *parse_file_label(char *str, t_file *file, off_t bytes)
{
    t_label         *tmp;
    char            *buffer;
    static  char    *string;
    int             ret;

    tmp = NULL;
 	if (!(string = ft_strnew(1)))
		return (NULL);
    if (lseek(file->fd, bytes, SEEK_SET) < 0)
        return (reset_file_read(file, bytes, &string, NULL));
    while ((ret = ft_readline(file->fd, &string, &buffer)) > 0)
    {
        if (!tmp)
        {
            if ((tmp = parse_line_label(&buffer, str, file)))
                if (find_instruction(&buffer, buffer + (ret - 1), file) != EXIT_ERROR)
                    return (reset_file_read(file, bytes, &string, tmp));
        }
        else
        {
            if (find_instruction(&buffer, buffer + (ret - 1), file) != EXIT_ERROR)
            {
                printf("last\n");   
                return (reset_file_read(file, bytes, &string, tmp));
            }
            return (reset_file_read(file, bytes, &string, NULL));
        }  
    }
    return (reset_file_read(file, bytes, &string, NULL));
}
