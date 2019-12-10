/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:22:05 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:19:53 by crath            ###   ########.fr       */
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
