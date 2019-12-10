/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:24:49 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:19:49 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		or(t_list *carry, t_vm *vm)
{
	int j;
	int n;

	j = carry->coding >> 2;
	n = (int)get_rdi_val(carry, j >> 2, 4, vm) |
		(int)get_rdi_val(carry, j & 3, 4, vm);
	carry->registry[vm->map[carry->pc].val - 1] = n;
	carry->carry = carry->registry[vm->map[carry->pc].val - 1] == 0 ? 1 : 0;
	carry->pc = iterate(&carry->pc, 1);
	return (0);
}
