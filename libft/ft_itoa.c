/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:45:16 by lseema            #+#    #+#             */
/*   Updated: 2020/11/15 15:43:32 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		cap(int n, int minus)
{
	int len;

	len = 1;
	while ((n /= 10))
		len++;
	return (minus + len);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		znak;
	int		dig;

	znak = (n < 0) ? 1 : 0;
	len = cap(n, znak);
	if ((str = ft_strnew(len)))
	{
		str[len--] = '\0';
		while (len >= znak)
		{
			dig = n % 10;
			str[len--] = (dig < 0 ? dig * -1 : dig) + '0';
			n /= 10;
		}
		if (znak)
			str[0] = '-';
	}
	return (str);
}
