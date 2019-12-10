/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_order_changing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		reorder(int *a, int j, char **tmp, t_vm *vm)
{
	int i;
	int n;

	i = -1;
	while (++i < vm->number_of_bots)
		tmp[i] = NULL;
	i = -1;
	while (++i < vm->number_of_bots)
	{
		if (a[i] != 0)
			tmp[a[i] - 1] = vm->bot_filenames[i];
	}
	i = 0;
	n = 0;
	while (j-- > 0)
	{
		while (tmp[n] != NULL)
			n++;
		while (a[i] != 0)
			i++;
		tmp[n] = vm->bot_filenames[i++];
	}
	i = -1;
	while (++i < vm->number_of_bots)
		vm->bot_filenames[i] = tmp[i];
}

void			bot_order_changing(t_vm *vm, int *a)
{
	char		*tmp[4];
	int			i;
	int			j;

	if ((a[0] != 0 && (a[0] == a[1] || a[0] == a[2] || a[0] == a[3] ||
		a[0] == a[4])) || (a[1] != 0 && (a[1] == a[2] || a[1] == a[3] ||
		a[1] == a[4])) || (a[2] != 0 && (a[2] == a[3] || a[2] == a[4])) ||
		(a[3] != 0 && a[3] == a[4]))
		err_ex("two bots can't have the same order\n");
	i = -1;
	j = 0;
	while (++i < vm->number_of_bots)
	{
		if (a[i] != 0 && a[i] != i + 1)
		{
			if (a[i] > vm->number_of_bots)
				err_ex("number after [-n] is bigger than bots' amount\n");
			j++;
		}
	}
	if (j == 0)
		return ;
	j = 4 - j;
	reorder(a, j, tmp, vm);
}
