/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:15:25 by lseema            #+#    #+#             */
/*   Updated: 2020/12/11 22:12:27 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *p;
	unsigned char ch;

	ch = (unsigned char)c;
	p = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*p == ch)
			return (p);
		p++;
	}
	return (NULL);
}
