/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:59:41 by lseema            #+#    #+#             */
/*   Updated: 2020/12/11 22:12:28 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;
	long int	pos;

	j = 0;
	i = 0;
	if (needle[0] == '\0')
		return ((char*)&haystack[0]);
	pos = -1;
	while (haystack[i] != '\0' && needle[j] != '\0')
	{
		while (haystack[i] == needle[j] && haystack[i] != '\0')
		{
			if (pos == -1)
				pos = i;
			i++;
			j++;
		}
		if (needle[j] == '\0')
			return ((char*)&haystack[pos]);
		i = (i - j) + 1;
		j = 0;
		pos = -1;
	}
	return (NULL);
}
