/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:20:30 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:18:02 by crath            ###   ########.fr       */
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
