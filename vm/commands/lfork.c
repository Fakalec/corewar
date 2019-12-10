/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		lfork(t_list *carry, t_vm *vm)
{
	fork_carry(carry, vm, get_short(vm->map, carry->pc));
	iterate(&carry->pc, 2);
	vm->processes++;
	choose_sound(vm, 3);
	if (vm->v == 1 && vm->cycle >= vm->cycle_to_start)
		system("afplay corsound/oh_my.mp3&");
	return (0);
}
