/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:19:22 by lseema            #+#    #+#             */
/*   Updated: 2019/05/26 21:35:14 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	long int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while ((s[i] != c) && (i >= 0))
		i--;
	if (i == -1)
		return (NULL);
	return ((char*)&s[i]);
}
