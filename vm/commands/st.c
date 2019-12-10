/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:25:06 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:19:48 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		st(t_list *carry, t_vm *vm)
{
	int j;
	int r;
	int n;

	j = (carry->coding >> 2) & 3;
	r = carry->pc;
	iterate(&carry->pc, 1);
	if (j == REG_CODE)
	{
		carry->registry[vm->map[carry->pc].val - 1] =
			carry->registry[vm->map[r].val - 1];
	}
	else
	{
		n = carry->op;
		iterate(&n, get_short(vm->map, carry->pc) % IDX_MOD);
		uint_to_map(carry->registry[vm->map[r].val - 1], carry->id, vm, n);
	}
	iterate(&carry->pc, j == REG_CODE ? 1 : 2);
	return (0);
}
