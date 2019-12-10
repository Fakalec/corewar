/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:21:14 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:18:04 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		fork_op(t_list *carry, t_vm *vm)
{
	fork_carry(carry, vm, get_short(vm->map, carry->pc) % IDX_MOD);
	iterate(&carry->pc, 2);
	vm->processes++;
	choose_sound(vm, 3);
	return (0);
}
