/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:27:31 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 12:27:53 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*dec_to_str(char *buf, size_t size,
		unsigned long long n, unsigned flags)
{
	buf[0] = 0;
	buf[1] = 0;
	if ((flags & SIGNED_FLAG) && (long long)n < 0)
	{
		buf[0] = '-';
		n = -(long long)n;
	}
	buf[--size] = '\0';
	while (n >= 10)
	{
		buf[--size] = n % 10 + '0';
		n /= 10;
	}
	buf[--size] = n % 10 + '0';
	if (buf[0] == 0 && flags & SIGNED_FLAG)
	{
		if (flags & SHOWSIGN_FLAG)
			buf[0] = '+';
		else if (flags & SPACE_FLAG)
			buf[0] = ' ';
	}
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

int			ft_print_dec(unsigned long long n, t_format *fmt)
{
	char	buf[23];
	char	*digits;
	int		len;
	int		ret;

	ret = 0;
	digits = dec_to_str(buf, sizeof(buf), n, fmt->flags);
	len = ft_strlen(digits);
	if (!(fmt->flags & LEFTFORMAT_FLAG) && !(fmt->flags & ZERO_FLAG))
		ret += ft_putnchar(' ', (size_t)get_space_count(fmt, len, buf[0]));
	ret += ft_putstr(buf);
	ret += ft_putnchar('0', (size_t)get_zero_count(fmt, len, buf[0]));
	if (n != 0 || !(fmt->flags & PRECISION && fmt->precision == 0))
		ret += ft_putstr(digits);
	else if (fmt->flags & WIDTH)
		ret += ft_putchar(' ');
	if (fmt->flags & LEFTFORMAT_FLAG)
		ret += ft_putnchar(' ', (size_t)get_space_count(fmt, len, buf[0]));
	return (ret);
}
