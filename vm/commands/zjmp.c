/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:26:05 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:19:44 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		zjmp(t_list *carry, t_vm *vm)
{
	if (carry->carry == 1)
	{
		carry->pc =
			iterate(&carry->op, get_short(vm->map, carry->pc) % IDX_MOD);
	}
	else
		iterate(&carry->pc, 2);
	return (0);
}
