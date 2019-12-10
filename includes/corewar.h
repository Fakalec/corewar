/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include <ncurses.h>
# include <time.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define IS_VALID_OPCODE(x)		(x > 0 && x < 17)
# define REG_CHECK(x)			(x < 1 || x > REG_NUMBER)

typedef struct		s_map
{
	unsigned char	val;
	int				id;
	int				bold;
	int				live;
	int				live_id;
}					t_map;

typedef struct		s_op
{
	char			*name;
	int				args_num;
	int				args[3];
	int				opcode;
	int				cycles;
	char			*opcode_description;
	int				coding;
	int				label_size;
}					t_op;

typedef struct		s_bot
{
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned char	bot[CHAMP_MAX_SIZE];
	long			size;
	int				lives_in_cycle;
	int				last_live;
}					t_bot;

typedef struct		s_list
{
	int				registry[REG_NUMBER];
	int				pc;
	int				op;
	int				opcode;
	int				coding;
	int				id;
	int				carry;
	int				cycles;
	int				alive;
	struct s_list	*next;
}					t_list;

typedef struct		s_vm
{
	t_list			*carry_list_head;
	int				v;
	int				a_flag;
	int				dump;
	int				number_of_bots;
	char			*bot_filenames[4];
	t_bot			bot[MAX_PLAYERS];
	t_map			map[MEM_SIZE];
	int				(*functions[16])(t_list *carry, struct s_vm *);
	int				cycle;
	int				cycle_to_start;
	unsigned int	cycle_alive;
	unsigned int	cycle_to_die;
	int				checks_count;
	int				processes;
	int				lives_in_cycle;
	int				fps;
	int				last;
	int				s;
}					t_vm;

unsigned int		get_uint(t_map *map, int n);
short				get_short(t_map *map, int n);
void				uint_to_map(unsigned int n, int id, t_vm *vm, int i);
int					get_rdi_val(t_list *carry, int t_rdi, int d, t_vm *vm);
int					iterate(int *pc, int n);
void				fork_carry(t_list *orig_carry, t_vm *vm, int pos);

extern t_op			g_op_tab[17];

int					ft_printf(const char *fmt, ...);

void				parsing_args(int argc, char **argv, t_vm *vm, int i);
int					str_cmp(char *a, char *b);
void				flag_searcher(t_vm *vm, char **argv, int *i);
void				cor_files_reader(t_vm *vm);
void				bot_order_changing(t_vm *vm, int *a);
int					check_coding_and_regs(t_list *carry, t_vm *vm);
void				corewar(t_vm *vm);
void				run_cycle(t_vm *vm);
void				err_ex(char *error_message);
void				to_show_usage(void);
void				introduction_players(t_vm *vm);
void				dump_memory(t_vm *vm);

int					live(t_list *carry, t_vm *vm);
int					ld(t_list *carry, t_vm *vm);
int					st(t_list *carry, t_vm *vm);
int					add(t_list *carry, t_vm *vm);
int					sub(t_list *carry, t_vm *vm);
int					and(t_list *carry, t_vm *vm);
int					or(t_list *carry, t_vm *vm);
int					xor(t_list *carry, t_vm *vm);
int					zjmp(t_list *carry, t_vm *vm);
int					ldi(t_list *carry, t_vm *vm);
int					sti(t_list *carry, t_vm *vm);
int					fork_op(t_list *carry, t_vm *vm);
int					lld(t_list *carry, t_vm *vm);
int					lldi(t_list *carry, t_vm *vm);
int					lfork(t_list *carry, t_vm *vm);
int					aff(t_list *carry, t_vm *vm);

void				draw_ncurses(t_vm *vm);
void				start_ncurses(void);
void				end_ncurses(t_vm *vm);
void				pause_ncurses(t_vm *vm);
void				keys_control(t_vm *vm);
void				choose_sound(t_vm *vm, int i);

#endif
