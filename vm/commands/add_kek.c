/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		add(t_list *carry, t_vm *vm)
{
	int r1;
	int r2;

	r1 = carry->pc;
	r2 = iterate(&carry->pc, 1);
	iterate(&carry->pc, 1);
	carry->registry[vm->map[carry->pc].val - 1] =
	carry->registry[vm->map[r1].val - 1] + carry->registry[vm->map[r2].val - 1];
	carry->carry = carry->registry[vm->map[carry->pc].val - 1] == 0 ? 1 : 0;
	carry->pc = iterate(&carry->pc, 1);
	return (0);
}
