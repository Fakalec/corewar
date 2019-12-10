/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	choose_sound(t_vm *vm, int i)
{
	if (vm->v == 1 || vm->v == -1)
	{
		if (i == 0)
			system("afplay corsound/t3.mp3&");
		else if (i == 1)
			system("afplay corsound/dramatic.swf.mp3&");
		else if (vm->cycle >= vm->cycle_to_start && vm->v != -1)
		{
			if (i == 2)
				system("afplay corsound/ws.mp3&");
			else if (i == 3)
				system("afplay corsound/oh_my.mp3&");
		}
	}
}
