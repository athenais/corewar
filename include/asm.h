/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrunet <abrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:58:03 by abrunet           #+#    #+#             */
/*   Updated: 2019/08/15 16:36:17 by abrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "op.h"
#include <stdint.h>
#include <sys/types.h>
#include "../libft/libft.h"

# define ASM_EXT		".s"

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
	int					dir_size;
	int					ocp;
	unsigned int		wr_size;
	int					oct;
	unsigned int		param[3];
}						t_inst;

typedef struct			s_lab
{
	char				*name;
	unsigned int		start;
	unsigned int		filler;
	int					size;
	struct	s_lab		*next;
	
}						t_lab;

typedef struct			s_label
{
	unsigned int		start;
	char				*name;
	struct	s_label		*next;
}						t_label;

typedef	struct			s_file
{
	int					fd;
	int					fd_cor;
	off_t				bytes;
	char				*cor;
	struct 	header_s	*hd;
	struct	s_label		*label;
	struct	s_lab		*lab_list;
	struct	s_op const	*op_tab;
}						t_file;

typedef struct		s_op
{
	char			*name;
	int				arg;
	t_arg_type		type[3];
	int				op_code;
	int				ocp;
	int				dir_size;
}					t_op;

int			check_extension(char *str);
int			read_file(t_file *file);
int			s_to_cor(char *file_name, t_file *file);
int	     	get_champ_name(t_file *file, char **wd, char *ptr, char **end);
int		    get_comment(t_file *file, char **wd, char *ptr, char **end);
int		    get_label(t_file *file, char **wd, char *ptr, char **end);
int			get_instruction(t_file *file, char **wd, char *ptr, char **end);
void		init_inst(t_inst *inst, t_file *file);
int         handle_instruction(t_file *file, char **str, t_inst *inst);
int         valid_instruction_format(char *str, int type);
int			is_instruction(char *str, t_op const *op_tab);
int	        write_to_cor(unsigned int byte, int oct, t_file *file);
char		*ft_itoa_bse(unsigned int n, int base, int len);
int    		generate_ocp(int *ocp, t_arg_type type, int *shift);
void    	write_header(t_file *file);
int    		write_instruction(t_file *file, t_inst inst);
void        free_split(char **split);
int			ft_trim(char *split, char **s, int arg);
int			parse_lab_list(t_file *file);
int			inc_size(t_inst *inst, int type);
int64_t     asm_atoi(char **string, int shrt);
t_lab       *lab_list(char **str, t_file *file, t_inst *inst);
t_label		*make_label(char **wd, t_file *file, unsigned int start);
t_label		*parse_file_label(char *str, t_file *file, off_t bytes);

#endif
