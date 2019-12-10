/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_oct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:39:33 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 12:39:35 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*oct_to_str(char *buf, size_t size,
		unsigned long long n, unsigned flags)
{
	buf[0] = 0;
	buf[1] = 0;
	buf[--size] = '\0';
	if (flags & HASH_FLAG && n)
		buf[0] = '0';
	while (n >= 8)
	{
		buf[--size] = n % 8 + '0';
		n /= 8;
	}
	buf[--size] = n % 8 + '0';
	return (&(buf[size]));
}

static int	get_zero_count(t_format *fmt, int len, char sign)
{
	int		count;

	count = 0;
	if (fmt->flags & PRECISION)
		count = fmt->precision - len;
	else if (fmt->flags & WIDTH && fmt->flags & ZERO_FLAG)
		count = fmt->width - (len + (sign != 0));
	return (count > 0 ? count : 0);
}

static int	get_space_count(t_format *fmt, int len, char sign)
{
	int		count;

	count = 0;
	if (fmt->flags & WIDTH)
	{
		if (fmt->flags & PRECISION)
			len = fmt->precision > len ? fmt->precision : len;
		len += (sign != 0);
		count = fmt->width - len;
	}
	return (count > 0 ? count : 0);
}

int			ft_print_oct(unsigned long long n, t_format *fmt)
{
	char	buf[25];
	char	*digits;
	int		len;
	int		ret;

	ret = 0;
	digits = oct_to_str(buf, sizeof(buf), n, fmt->flags);
	len = ft_strlen(digits);
	if (!(fmt->flags & LEFTFORMAT_FLAG) && !(fmt->flags & ZERO_FLAG))
		ret += ft_putnchar(' ', (size_t)get_space_count(fmt, len, buf[0]));
	if (!(fmt->flags & PRECISION && fmt->precision > len))
		ret += ft_putstr(buf);
	if (!n && fmt->flags & PRECISION && fmt->precision == 0
			&& fmt->flags & HASH_FLAG)
		ret += ft_putchar('0');
	ret += ft_putnchar('0', (size_t)get_zero_count(fmt, len, buf[0]));
	if (n != 0 || (!(fmt->flags & PRECISION && fmt->precision == 0)))
		ret += ft_putstr(digits);
	else if (fmt->flags & WIDTH)
		ret += ft_putchar(' ');
	if (fmt->flags & LEFTFORMAT_FLAG)
		ret += ft_putnchar(' ', (size_t)get_space_count(fmt, len, buf[0]));
	return (ret);
}
