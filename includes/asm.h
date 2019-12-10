/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>

# define SEPAR		';'
# define BOT_SIZE	2048

typedef struct		s_list
{
	char			*str;
	int				n;
	int				p;
	int				name_len;
	struct s_list	*next;
}					t_list;

typedef struct		s_asm
{
	char			*f;
	char			*name;
	char			*comment;
	char			*cor_f_name;
	unsigned char	code[BOT_SIZE];
	int				size;
	int				arg_flag;
	int				t_dir_size;
	int				cor_fd;
	t_list			*op_labels;
}					t_asm;

typedef struct		s_back
{
	unsigned char	*buf;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned char	code[BOT_SIZE];
	unsigned int	size;
}					t_back;

typedef struct		s_op
{
	char			*name;
	int				args_num;
	int				args[3];
	int				opcode;
	int				cycles;
	char			*opcode_description;
	int				codage;
	int				label_size;
}					t_op;

int					str_len(char *str);
void				err_ex(char *error_message);
int					check_char(char c);
int					ui_cod(unsigned int num, int n, t_asm *s);
int					us_cod(unsigned short num, int n, t_asm *s);

int					check_regis(char *file, int i);
int					check_norm(char *file, int i);
int					check_wrong(char *file, int i);

void				close_wrong_par(int n, int parameter, int i, t_asm *s);
void				*close_lex(char *file, int n);

extern t_op			g_op_tab[17];

void				input_file(char *file_name, t_asm *s);
void				make_dot_cor(char *s_file_name, t_asm *s);
void				output_dot_cor(t_asm *s);

int					val_translate(t_asm *s);
int					str_cmp(char *a, char *b);

t_list				*take_operat_or_name(int i, t_asm *s);

void				translate_opers(int i, int opcode, t_asm *s);

int					take_reg_val(int i, t_asm *s);
int					take_norm_val(int i, t_asm *s);
int					take_wrong_val(int i, t_asm *s);

void				validate_argument(char *file, int i);

void				init_struct(t_asm *s);
void				free_every(t_asm *s);
void				remake_package(char *dir_name, t_asm *s);

void				backward(char *file);

int					arg_output(int fd, int i, t_back *rev);

#endif
