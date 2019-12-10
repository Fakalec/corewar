/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:38:19 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 12:38:20 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*hex_to_str(char *buf, size_t size,
		unsigned long long n, t_format *f)
{
	size_t	i;
	char	hex_table[16];

	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	i = -1;
	while (++i < 10)
		hex_table[i] = i + '0';
	hex_table[i] = (f->flags & CAPS_FLAG) ? 'A' : 'a';
	while (++i < 16)
		hex_table[i] = hex_table[i - 1] + 1;
	buf[--size] = '\0';
	while (n >= 16)
	{
		buf[--size] = hex_table[n % 16];
		n /= 16;
	}
	buf[--size] = hex_table[n % 16];
	if ((f->flags & HASH_FLAG && n) || f->spec == 'p')
	{
		buf[0] = '0';
		buf[1] = f->flags & CAPS_FLAG ? 'X' : 'x';
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
		count = fmt->width - (len + (sign != 0) * 2);
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
		len += (sign != 0) * 2;
		count = fmt->width - len;
	}
	return (count > 0 ? count : 0);
}

int			ft_print_hex(unsigned long long n, t_format *fmt)
{
	char	buf[25];
	char	*digits;
	int		len;
	int		ret;

	ret = 0;
	digits = hex_to_str(buf, sizeof(buf), n, fmt);
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

int			ft_print_p(t_format *fmt, va_list args)
{
	unsigned long long	num;
	int					ret;
	void				*ptr;

	ret = 0;
	fmt->flags |= HASH_FLAG;
	ptr = va_arg(args, void*);
	num = (unsigned long long)ptr;
	ret = ft_print_hex(num, fmt);
	return (ret);
}
