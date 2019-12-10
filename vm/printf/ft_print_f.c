/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:28:11 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 12:31:55 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			*ft_return_special_cases(int flag[2], t_format *lst,
		t_float *flt)
{
	char	*res;

	res = NULL;
	if (!flag[0] && !flag[1])
	{
		flt->spec_value = 2;
		if (lst->flags & CAPS_FLAG)
			res = "INF";
		else
			res = "inf";
	}
	else if (!flag[0] && flag[1])
	{
		flt->spec_value = 1;
		if (lst->flags & CAPS_FLAG)
			res = "NAN";
		else
			res = "nan";
	}
	return (res);
}

static char			*ft_nan_inf(t_float *flt, t_format *lst)
{
	int					flag[2];
	int					i;
	double				tmp;
	unsigned long long	n;

	(void)lst;
	i = 0;
	flag[0] = 0;
	flag[1] = 0;
	tmp = (double)flt->x;
	tmp = tmp < 0 ? -tmp : tmp;
	ft_memcpy(&n, &tmp, sizeof(n));
	if ((n & BASE) < BASE)
		flag[0] = 1;
	if ((n & MANTIS) != 0)
		flag[1] = 1;
	return (ft_return_special_cases(flag, lst, flt));
}

static char			*ft_convert_to_str(t_float *flt, t_format *lst)
{
	char		*res;
	long		f[2];
	long double	ld;
	char		*tmp;

	ld = flt->x;
	(ld < 0) ? (ld *= -1) : 0;
	f[0] = (long)ld;
	f[1] = (long)((ld - f[0]) * (ft_power(10, lst->precision + 1)));
	(f[1] % 10 > 4) ? (f[1] = f[1] / 10 + 1) : (f[1] /= 10);
	if (f[1] == 0)
	{
		f[0]--;
		f[1] = ft_power(10, lst->precision);
	}
	if ((int)ft_strlen(ft_itoa(f[1])) > lst->precision)
	{
		f[0]++;
		tmp = (ft_itoa(f[1]));
		tmp++;
		res = ft_strjoin(ft_strjoin(ft_itoa(f[0]), "."), tmp);
	}
	else
		res = ft_strjoin(ft_strjoin(ft_itoa(f[0]), "."), ft_itoa(f[1]));
	return (res);
}

static long double	ft_read_f(t_format *lst, va_list va)
{
	long double	ld;

	if (lst->flags & L_FLAG)
		ld = va_arg(va, long double);
	else
		ld = (long double)va_arg(va, double);
	return (ld);
}

int					ft_print_f(t_format *lst, va_list va)
{
	t_float		*flt;
	char		*res;

	if (!(lst->flags & PRECISION))
		lst->precision = 6;
	flt = (t_float*)malloc(sizeof(t_float));
	flt->x = ft_read_f(lst, va);
	flt->spec_value = 0;
	flt->sign = ((long)((float)(flt->x)) & 0x800000000000000) != 0;
	res = ft_nan_inf(flt, lst);
	if (res)
		return (ft_minus_flag(res, lst, flt));
	res = ft_convert_to_str(flt, lst);
	return (ft_minus_flag(res, lst, flt));
}
