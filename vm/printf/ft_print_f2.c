/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_f2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:32:47 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 12:32:55 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_return_char(t_float *flt, t_format *lst)
{
	if (flt->sign != 0 && flt->spec_value != 1)
	{
		ft_putchar('-');
	}
	else
	{
		if (lst->flags & SHOWSIGN_FLAG && flt->spec_value != 1)
			ft_putchar('+');
		if ((lst->flags & ZERO_FLAG) && !(lst->flags & SPACE_FLAG)
				&& !flt->spec_value)
			ft_putchar('0');
		if (lst->flags & SPACE_FLAG)
			ft_putchar(' ');
	}
}

static int			ft_max(int a, int b)
{
	if (b > a)
		return (b);
	else
		return (a);
}

long				ft_power(int base, int power)
{
	int		i;
	long	res;

	i = 0;
	res = 1;
	while (i < power)
	{
		res *= base;
		i++;
	}
	return (res);
}

int					ft_minus_flag(char *res, t_format *lst, t_float *flt)
{
	int		l;

	lst->width = ft_max(lst->width, ft_strlen(res) + flt->sign);
	l = 0;
	if (lst->flags & LEFTFORMAT_FLAG)
	{
		ft_return_char(flt, lst);
		ft_putstr(res);
		l = ft_putnchar(' ', lst->width - (ft_strlen(res) + flt->sign));
	}
	else
	{
		if (lst->flags & ZERO_FLAG && !flt->spec_value)
		{
			ft_return_char(flt, lst);
			l = ft_putnchar('0', lst->width - ft_strlen(res) - flt->sign);
		}
		else
		{
			l = ft_putnchar(' ', lst->width - ft_strlen(res) - flt->sign);
			ft_return_char(flt, lst);
		}
		ft_putstr(res);
	}
	return (l + ft_strlen(res) + flt->sign);
}
