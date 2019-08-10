#ifndef ASM_H
# define ASM_H

#include "op.h"
#include <stdint.h>
#include <sys/types.h>
#include "../libft/libft.h"

# define ASM_EXT		".s"

enum					e_flag {
	inactive,
	active
};

enum					e_byte {
	c = 8,
	shrt = 16,
	i = 32	
};

enum					e_type {
	label,
	instruction
};

typedef struct			s_inst 
{
	int					index;
	int					ocp;
	int					param[3];
}						t_inst;

typedef struct			s_label
{
	int					flag;
	char				*name;
	struct	s_label		*next;
}						t_label;

typedef	struct			s_file
{
	int					fd;
	int					fd_cor;
	off_t				bytes;
	off_t				str_len;
	char				*cor;
	struct 	header_s	*hd;
	struct	s_label		*label;
	struct	s_op 		*op_tab;
}						t_file;

int			check_extension(char *str);
int			s_to_cor(char *file_name, t_file *file);
void		define_op_tab(t_op **tab);
int	     	get_champ_name(t_file *file, char **wd, char *ptr, char **end);
int		    get_comment(t_file *file, char **wd, char *ptr, char **end);
int		    get_label(t_file *file, char **wd, char *ptr, char **end);
int			get_instruction(t_file *file, char **wd, char *ptr, char **end);
int         handle_instruction(t_file *file, char **str, t_inst *inst);
int         valid_instruction_format(char *str, int type);
int			is_instruction(char *str, t_op *op_tab);
int			ft_trim(char **split, int arg);
int	        write_to_cor(int byte, int oct, t_file *file);
char		*ft_itoa_bse(int n, int base, int len);
void    	generate_ocp(int *ocp, t_arg_type type, int *shift);
void    	write_header(t_file *file);
int    		write_instruction(t_file *file, t_inst inst);
t_label     *reset_file_read(t_file *file, off_t bytes, char **str, t_label *label);
t_label		*make_label(char **wd, t_file *file);
t_label		*label_exist(char *str, t_file *file);
t_label		*parse_file_label(char *str, t_file *file, off_t bytes);

#endif
