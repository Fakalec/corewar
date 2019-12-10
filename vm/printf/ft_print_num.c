/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:38:57 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 12:38:58 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	cast_signed(unsigned long long *n, t_format *fmt, va_list args)
{
	if (fmt->flags & J_FLAG)
		*n = va_arg(args, intmax_t);
	else if (fmt->flags & Z_FLAG)
		*n = va_arg(args, size_t);
	else if (fmt->flags & LL_FLAG)
		*n = va_arg(args, long long);
	else if (fmt->flags & L_FLAG)
		*n = va_arg(args, long);
	else if (fmt->flags & HH_FLAG)
		*n = (signed char)va_arg(args, int);
	else if (fmt->flags & H_FLAG)
		*n = (short)va_arg(args, int);
	else
		*n = va_arg(args, int);
}

static void	cast_unsigned(unsigned long long *n, t_format *fmt, va_list args)
{
	if (fmt->flags & J_FLAG)
		*n = va_arg(args, uintmax_t);
	else if (fmt->flags & Z_FLAG)
		*n = va_arg(args, size_t);
	else if (fmt->flags & LL_FLAG)
		*n = va_arg(args, unsigned long long);
	else if (fmt->flags & L_FLAG)
		*n = va_arg(args, unsigned long);
	else if (fmt->flags & HH_FLAG)
		*n = (unsigned char)va_arg(args, unsigned int);
	else if (fmt->flags & H_FLAG)
		*n = (unsigned short)va_arg(args, unsigned int);
	else
		*n = va_arg(args, unsigned int);
}

int			ft_print_num(t_format *fmt, va_list args)
{
	int					ret;
	unsigned long long	n;

	ret = 0;
	if (fmt->spec == 'd')
	{
		fmt->flags |= SIGNED_FLAG;
		cast_signed(&n, fmt, args);
	}
	else
		cast_unsigned(&n, fmt, args);
	if (fmt->spec == 'd' || fmt->spec == 'u')
		ret = ft_print_dec(n, fmt);
	else if (fmt->spec == 'o')
		ret = ft_print_oct(n, fmt);
	else if (fmt->spec == 'x')
		ret = ft_print_hex(n, fmt);
	return (ret);
}
