/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:24:32 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:19:50 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		lldi(t_list *carry, t_vm *vm)
{
	int j;
	int n;

	j = carry->coding >> 2;
	n = ((int)get_rdi_val(carry, j >> 2, 2, vm) +
		(int)get_rdi_val(carry, j & 3, 2, vm));
	j = carry->op;
	iterate(&j, n);
	n = get_uint(vm->map, j);
	carry->registry[vm->map[carry->pc].val - 1] = n;
	carry->carry = (n == 0 ? 1 : 0);
	iterate(&carry->pc, 1);
	return (0);
}
