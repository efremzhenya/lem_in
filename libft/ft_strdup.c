/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:26:56 by lseema            #+#    #+#             */
/*   Updated: 2020/12/11 22:12:27 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	len;

	len = 0;
	while (src[len] != '\0')
		len++;
	if (!(dst = malloc(sizeof(char) * len + 1)))
		return (NULL);
	else
	{
		len = 0;
		while (src[len] != '\0')
		{
			dst[len] = src[len];
			len++;
		}
		dst[len] = '\0';
		return (dst);
	}
}
