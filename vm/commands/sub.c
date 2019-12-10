/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:25:32 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:19:47 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		sub(t_list *carry, t_vm *vm)
{
	int r1;
	int r2;

	r1 = carry->pc;
	r2 = iterate(&carry->pc, 1);
	iterate(&carry->pc, 1);
	carry->registry[vm->map[carry->pc].val - 1] =
	carry->registry[vm->map[r1].val - 1] - carry->registry[vm->map[r2].val - 1];
	carry->carry = carry->registry[vm->map[carry->pc].val - 1] == 0 ? 1 : 0;
	carry->pc = iterate(&carry->pc, 1);
	return (0);
}
