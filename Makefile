# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dstracke <crath@student.42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/21 15:54:02 by dstracke          #+#    #+#              #
#    Updated: 2019/11/21 20:51:22 by dstracke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM				=	corewar
ASM				=	asm

VM_SRC			=	bot_order_changing.c check_regs_and_coding.c \
					corewar.c main.c op.c parsing_args.c read_files.c \
					runcycle.c search_flags.c sound.c start_visualization.c \
					stdout.c visualization_keys.c visualization_ncurses.c

VM_INS_SRC		=	live.c ld.c st.c add.c sub.c and.c or.c \
					xor.c zjmp.c ldi.c sti.c fork.c lld.c lldi.c \
					lfork.c	aff.c fn.c iterate.c

PRINTF_SRC		=	ft_printf.c	ft_create_format.c ft_itoa.c \
					ft_memcpy.c ft_print_c.c ft_print_dec.c \
					ft_print_f.c ft_print_f2.c ft_print_format.c \
					ft_print_hex.c ft_print_num.c ft_print_oct.c \
					ft_print_s.c ft_putchar.c ft_putnchar.c \
					ft_putstr.c  ft_putwchar.c \
					ft_putwstr.c ft_read_format.c ft_strdup.c \
					ft_strjoin.c ft_strlen.c ft_wstrlen.c

ASM_SRC			=	main.c arg_output.c backward.c check_regis.c \
					helpers.c invalidates.c op.c remake_package.c \
					take_operat_and_name.c take_vals.c translate_opers.c \
					val_translate.c validate_argument.c


CC				=	gcc
FLAGS			=	-Wall -Werror -Wextra -Wshadow
NCURSES_FLAG	=	-lncurses

VM_OBJ			=	$(addprefix $(VM_OBJ_DIR), $(VM_SRC:.c=.o))
VM_INS_OBJ		=	$(addprefix $(VM_OBJ_DIR), $(VM_INS_SRC:.c=.o))
VM_PRINT_OBJ	=	$(addprefix $(VM_OBJ_DIR), $(PRINTF_SRC:.c=.o))
ASM_OBJ			=	$(addprefix $(ASM_OBJ_DIR), $(ASM_SRC:.c=.o))
INC_FILES		=	$(addprefix $(INC_DIR), $(INC))

VM_SRC_DIR		=	./vm/
VM_INS_SRC_DIR	=	./vm/commands/
ASM_SRC_DIR		=	./assembler/
VM_OBJ_DIR		=	./vm_obj/
ASM_OBJ_DIR		=	./assembler_obj/
PRINTF_DIR		=	./vm/printf/
INC_DIR			=	./includes/
INC				=	asm.h corewar.h op.h

NC				=	\033[0m
BLUE			=	\033[3;36m
RED				=	\033[3;31m

all: $(VM) $(ASM)

$(VM_OBJ_DIR)%.o: $(VM_SRC_DIR)%.c $(INC_FILES)
	@mkdir -p $(VM_OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(VM_OBJ_DIR)%.o: $(VM_INS_SRC_DIR)%.c $(INC_FILES)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(VM_OBJ_DIR)%.o: $(PRINTF_DIR)%.c
	@$(CC) $(FLAGS) -o $@ -c $<

$(VM): $(VM_OBJ) $(VM_INS_OBJ) $(VM_PRINT_OBJ)
	@echo "${BLUE}Compiling $(VM) with $(FLAGS) flags${NC}\n..."
	@$(CC) $(FLAGS) $(NCURSES_FLAG) -o $(VM) $(VM_OBJ) $(VM_INS_OBJ) $(VM_PRINT_OBJ)
	@echo "${BLUE}Done!${NC}"

$(ASM_OBJ_DIR)%.o: $(ASM_SRC_DIR)%.c $(INC_FILES)
	@mkdir -p $(ASM_OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

$(ASM): $(ASM_OBJ)
	@echo "${BLUE}Compiling $(ASM) with $(FLAGS) flags${NC}\n..."
	@$(CC) $(FLAGS) -o $(ASM) $(ASM_OBJ)
	@echo "${BLUE}Done!${NC}"


clean:
	@rm -rf $(VM_OBJ_DIR) $(ASM_OBJ_DIR) $(CMP_OBJ)
	@echo  "${RED}$(VM_OBJ_DIR) and $(ASM_OBJ_DIR) has been removed.${NC}"

fclean: clean
	@rm -rf $(VM) $(ASM) $(CMP)
	@echo "${RED}$(VM) and $(ASM) has been removed.${NC}"

re: fclean all

.PHONY: all clean fclean re
