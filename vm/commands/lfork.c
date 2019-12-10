/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:23:40 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:19:53 by crath            ###   ########.fr       */
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
