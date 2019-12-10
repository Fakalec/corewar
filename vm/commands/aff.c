/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		aff(t_list *carry, t_vm *vm)
{
	int n;

	if (vm->a_flag == 1)
	{
		n = carry->registry[vm->map[carry->pc].val - 1];
		write(1, "Aff: ", 5);
		write(1, &n, 1);
		write(1, "\n", 1);
	}
	iterate(&carry->pc, 1);
	return (0);
}
