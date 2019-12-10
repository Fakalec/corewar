/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:24:14 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:52:49 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		lld(t_list *carry, t_vm *vm)
{
	int n;
	int t;

	if ((carry->coding & 0x3c) == 0x34)
	{
		n = carry->op;
		iterate(&n, (short)get_short(vm->map, carry->pc) % MEM_SIZE);
		t = get_uint(vm->map, n);
		t = t > 0x7fffffff ? (t >> 16) | 0xffff0000 : t >> 16;
		iterate(&carry->pc, 2);
		carry->registry[vm->map[carry->pc].val - 1] = t;
	}
	else if ((carry->coding & 0x3c) == 0x24)
	{
		n = get_uint(vm->map, carry->pc);
		iterate(&carry->pc, 4);
		carry->registry[vm->map[carry->pc].val - 1] = n;
	}
	carry->carry = carry->registry[vm->map[carry->pc].val - 1] == 0 ? 1 : 0;
	carry->pc = iterate(&carry->pc, 1);
	return (0);
}
