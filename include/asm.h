#ifndef ASM_H
# define ASM_H

# define ASM_EXT		".s"
#include "op.h"
#include <stdint.h>

typedef struct		s_label
{
	char			*name;
	struct	s_label	*next;
}					t_label;

typedef	struct		s_file
{
	int				fd;
	char			name[PROG_NAME_LENGTH + 1];
	char			cmnt[COMMENT_LENGTH + 1];
	struct	s_label	*label;
	struct	s_op 	 *op_tab;

}					t_file;

int			check_extension(char *str);
int			translate_to_cor(char *file_name);
void		define_op_tab(t_op **tab);
int	     	get_champ_name(t_file *file, __unused char *wd, char *ptr, char *end);
int		    get_comment(t_file *file, __unused char *wd, char *ptr, char *end);
int		    get_label(t_file *file, char *wd, __unused char *ptr, __unused char *end);
int			get_instruction(t_file *file, char *wd, char *ptr, char *end);
int			is_instruction(char *str, t_op *op_tab);

#endif
