/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:22:15 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:20:10 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ldi(t_list *carry, t_vm *vm)
{
	int j;
	int n;

	j = carry->coding >> 2;
	j = ((int)get_rdi_val(carry, j >> 2, 2, vm) +
		(int)get_rdi_val(carry, j & 3, 2, vm)) % IDX_MOD;
	n = carry->op;
	iterate(&n, j);
	n = get_uint(vm->map, n);
	carry->registry[vm->map[carry->pc].val - 1] = n;
	iterate(&carry->pc, 1);
	return (0);
}
