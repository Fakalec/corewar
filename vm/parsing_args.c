/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:31:49 by crath             #+#    #+#             */
/*   Updated: 2019/09/25 20:20:39 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				str_cmp(char *a, char *b)
{
	while (*a && *b && *a == *b)
	{
		a += 1;
		b += 1;
	}
	return (*a == '\0' && *b == '\0');
}

static int		to_get_bot_order(char *str)
{
	if (str == NULL)
		err_ex("not enough arguments after [-n] flag\n");
	if (*str == '1' && *(str + 1) == '\0')
		return (1);
	else if (*str == '2' && *(str + 1) == '\0')
		return (2);
	else if (*str == '3' && *(str + 1) == '\0')
		return (3);
	else if (*str == '4' && *(str + 1) == '\0')
		return (4);
	if (*str >= '0' && *str <= '9')
		err_ex("only numbers 1 2 3 and 4 can be used after [-n] flag\n");
	else
		err_ex("you need spcify position after [-n] flag\n");
	return (0);
}

static char		*to_get_bot_name(char *str)
{
	int i;

	if (str == NULL)
		err_ex("missing bot name\n");
	i = 0;
	while (str[i])
		i++;
	if (*str == '-')
		err_ex("invalid flag\n");
	if (i <= 4)
		err_ex("bot name is invalid\n");
	if (str[i - 1] != 'r' || str[i - 2] != 'o' ||
		str[i - 3] != 'c' || str[i - 4] != '.')
		err_ex("bot name must have .cor extension\n");
	return (str);
}

void			parsing_args(int argc, char **argv, t_vm *vm, int i)
{
	int a[4];

	while (++i < 4)
		a[i] = 0;
	i = 0;
	flag_searcher(vm, argv, &i);
	while (++i < argc)
	{
		if (vm->number_of_bots == MAX_PLAYERS)
			err_ex("too many players\n");
		if (str_cmp(argv[i], "-n") &&
			(a[vm->number_of_bots] = to_get_bot_order(argv[i + 1])))
			i += 2;
		vm->bot_filenames[vm->number_of_bots++] = to_get_bot_name(argv[i]);
	}
	bot_order_changing(vm, a);
	vm->last = vm->number_of_bots;
}
