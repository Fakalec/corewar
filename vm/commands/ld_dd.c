/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ld(t_list *carry, t_vm *vm)
{
	int n;

	if ((carry->coding & 0x3c) == 0x34)
	{
		n = carry->op;
		iterate(&n, ((short)get_short(vm->map, carry->pc) % IDX_MOD) %
			MEM_SIZE);
		iterate(&carry->pc, 2);
		carry->registry[vm->map[carry->pc].val - 1] = get_uint(vm->map, n);
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
