/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:25:18 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:19:48 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		sti(t_list *carry, t_vm *vm)
{
	int j;
	int r;
	int n;

	j = carry->coding & 0xf;
	r = carry->pc;
	iterate(&carry->pc, 1);
	n = ((int)(get_rdi_val(carry, j >> 2, 2, vm) +
		get_rdi_val(carry, j & 3, 2, vm)) % IDX_MOD);
	j = carry->op;
	iterate(&j, n);
	uint_to_map(carry->registry[vm->map[r].val - 1], carry->id, vm, j);
	return (0);
}
