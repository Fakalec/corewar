/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		finish_him(t_vm *vm)
{
	if (vm->v == 1 && vm->cycle <= vm->cycle_to_start)
	{
		start_ncurses();
		draw_ncurses(vm);
		pause_ncurses(vm);
		end_ncurses(vm);
	}
	else
		ft_printf("Сompetitor %d, \"%s\", has won !\n",
			vm->last, vm->bot[vm->last - 1].name);
}

static void		play_and_visualize(t_vm *vm, clock_t *t1, clock_t *t2)
{
	keys_control(vm);
	if ((int)(*t1 * vm->fps / CLOCKS_PER_SEC) <
		(int)(*t2 * vm->fps / CLOCKS_PER_SEC) || vm->s == 1)
	{
		*t1 = clock();
		run_cycle(vm);
		if (vm->processes == 0)
		{
			while ((int)(*t1 * vm->fps / CLOCKS_PER_SEC) >=
				(int)(*t2 * vm->fps / CLOCKS_PER_SEC))
			{
				keys_control(vm);
				*t2 = clock();
			}
			draw_ncurses(vm);
			end_ncurses(vm);
			return ;
		}
	}
	*t2 = clock();
}

void			corewar(t_vm *vm)
{
	clock_t		t1;
	clock_t		t2;

	t1 = clock();
	t2 = clock() * CLOCKS_PER_SEC;
	while (vm->processes > 0)
	{
		if (vm->cycle == vm->cycle_to_start && vm->v == 1)
			start_ncurses();
		if (vm->dump == vm->cycle)
		{
			dump_memory(vm);
			return ;
		}
		if (vm->cycle >= vm->cycle_to_start && vm->v == 1)
			play_and_visualize(vm, &t1, &t2);
		else
			run_cycle(vm);
	}
	finish_him(vm);
}
