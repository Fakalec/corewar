/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:17:33 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 12:26:06 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*source;
	char	*dest;

	if (dst == src || n == 0)
		return (dst);
	dest = dst;
	source = (char *)src;
	i = 0;
	while (i < (int)n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dest);
}
