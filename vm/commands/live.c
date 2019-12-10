/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		set_the_bots_color(t_list *carry, t_vm *vm, int n)
{
	vm->map[carry->pc - 1].live_id = -n;
	if (vm->cycle >= vm->cycle_to_start)
	{
		vm->map[carry->pc - 1].bold = 49;
		vm->map[carry->pc - 1].live = 49;
	}
	else if (vm->cycle >= vm->cycle_to_start - 49)
	{
		vm->map[carry->pc - 1].bold = vm->cycle - vm->cycle_to_start + 50;
		vm->map[carry->pc - 1].live = vm->cycle - vm->cycle_to_start + 50;
	}
}

int				live(t_list *carry, t_vm *vm)
{
	int i;
	int n;

	vm->lives_in_cycle++;
	carry->alive = 1;
	n = get_uint(vm->map, carry->pc);
	i = 0;
	while (++i <= vm->number_of_bots)
	{
		if (n == -i)
		{
			vm->bot[i - 1].lives_in_cycle += 1;
			vm->bot[i - 1].last_live = vm->cycle + 1;
			set_the_bots_color(carry, vm, n);
			vm->last = -n;
			break ;
		}
	}
	iterate(&carry->pc, 4);
	return (0);
}
