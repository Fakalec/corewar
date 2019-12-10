/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:29:29 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:20:49 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		cycles_for_start(char *str)
{
	int		i;
	long	n;

	if (str == NULL)
		err_ex("Corewar needs at least one bot for work\n");
	n = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		n = (n * 10) + str[i++] - 48;
	if (i == 0 || str[i] != '\0')
		return (0);
	else if (n >= 1000000000)
		err_ex("Too many cycles\n");
	else if (i > 10)
		err_ex("Incorrect number of cycles\n");
	return (n);
}

static int		to_get_n_cycles_before_dump(char *str)
{
	int		i;
	long	n;

	if (str == NULL)
		err_ex("Corewar needs at least one bot for work\n");
	n = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		n = (n * 10) + str[i++] - 48;
	if (i == 0 || str[i] != '\0')
		err_ex("Incorrect number of cycles\n");
	else if (n >= 1000000000)
		err_ex("Too many cycles\n");
	else if (i > 10)
		err_ex("Incorrect number of cycles\n");
	return (n);
}

void			flag_searcher(t_vm *vm, char **argv, int *i)
{
	if (str_cmp(argv[1], "-a") && ++(*i))
		vm->a_flag = 1;
	else if (str_cmp(argv[1], "-v") && ++(*i))
	{
		vm->v = 1;
		*i += ((vm->cycle_to_start = cycles_for_start(argv[2])) > 0 ? 1 : 0);
	}
	else if (str_cmp(argv[1], "-dump"))
	{
		vm->dump = to_get_n_cycles_before_dump(argv[2]);
		*i += 2;
	}
}
