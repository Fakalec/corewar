/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_regs_and_coding.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:27:50 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:51:47 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		check_dir_ind(int c, int args, int *p, int op)
{
	if (c == DIR_CODE)
	{
		iterate(p, g_op_tab[op].label_size == 1 ? 2 : 4);
		if ((args & T_DIR) == 0)
			return (1);
	}
	else if (c == IND_CODE)
	{
		iterate(p, 2);
		if ((args & T_IND) == 0)
			return (1);
	}
	else
		return (1);
	return (0);
}

static int		check_opcode_with_coding(int op, int p, t_list *carry, t_vm *vm)
{
	int i;
	int error;
	int c;

	error = 0;
	i = -1;
	while (++i < g_op_tab[op].args_num)
	{
		c = (carry->coding >> (4 - i * 2)) & 3;
		if (c == REG_CODE)
		{
			if (!(g_op_tab[op].args[i] & T_REG) || REG_CHECK(vm->map[p].val))
				error = 1;
			iterate(&p, 1);
		}
		else if (check_dir_ind(c, g_op_tab[op].args[i], &p, op))
			error = 1;
	}
	if (error == 1)
		carry->pc = p;
	return (error);
}

int				check_coding_and_regs(t_list *carry, t_vm *vm)
{
	int error;
	int op;

	error = 0;
	carry->op = carry->pc;
	op = carry->opcode;
	iterate(&carry->pc, 1);
	if (g_op_tab[op].coding == 1)
	{
		carry->coding = vm->map[carry->pc].val >> 2;
		iterate(&carry->pc, 1);
		error = check_opcode_with_coding(op, carry->pc, carry, vm);
	}
	else if (g_op_tab[op].args[0] == T_REG &&
		(error = REG_CHECK(vm->map[carry->pc].val)))
		iterate(&carry->pc, 1);
	return (error == 0);
}
