/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization_keys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		getch_checker(t_vm *vm, int k)
{
	if (k == 113)
		vm->fps = (vm->fps > 10 ? vm->fps - 10 : 1);
	else if (k == 119)
		vm->fps -= (vm->fps > 1 ? 1 : 0);
	else if (k == 101)
		vm->fps += (vm->fps == 1000 ? 0 : 1);
	else if (k == 114)
		vm->fps = (vm->fps > 990 ? 1000 : vm->fps + 10);
	else if (k == 115)
	{
		vm->s = 1;
		return (1);
	}
	else if (k == 27)
	{
		vm->v = -1;
		endwin();
		return (1);
	}
	else if (k == 32)
		return (1);
	mvwprintw(stdscr, 4, 221, "%d      ", vm->fps);
	return (0);
}

void			pause_ncurses(t_vm *vm)
{
	int		k;

	wattron(stdscr, A_BOLD | COLOR_PAIR(50));
	mvwprintw(stdscr, 2, 217, "** PAUSED  **");
	while ((k = getch()))
	{
		if (getch_checker(vm, k))
			break ;
	}
	mvwprintw(stdscr, 2, 217, "** RUNNING **");
	wattroff(stdscr, A_BOLD | COLOR_PAIR(50));
}

void			keys_control(t_vm *vm)
{
	int		k;

	if (vm->s == 1)
	{
		vm->s = 0;
		pause_ncurses(vm);
		return ;
	}
	k = getch();
	if (k == 113)
		vm->fps = (vm->fps > 10 ? vm->fps - 10 : 1);
	else if (k == 119)
		vm->fps -= (vm->fps > 1 ? 1 : 0);
	else if (k == 101)
		vm->fps += (vm->fps < 1000 ? 1 : 0);
	else if (k == 114)
		vm->fps = (vm->fps < 990 ? vm->fps + 10 : 1000);
	else if (k == 27)
	{
		vm->v = -1;
		endwin();
	}
	else if (k == 32)
		pause_ncurses(vm);
}
