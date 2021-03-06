/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 23:37:07 by lseema            #+#    #+#             */
/*   Updated: 2020/12/06 18:03:13 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

size_t		ft_chrcount(char *line, char c)
{
	size_t	count;

	count = 0;
	while (*line)
	{
		if (*line == c)
			count++;
		line++;
	}
	return (count);
}

int			valid_int(char *argv)
{
	long long	res;
	int			i;

	res = ft_atoi(argv);
	if (ft_strlen(argv) > 11 || res < -2147483648 || res > 2147483647)
		return (0);
	i = 0;
	while (argv[i] != '\0')
		if ((argv[i] == '-' || argv[i] == '+') && i == 0 && ft_strlen(argv) > 1)
			i++;
		else if (!ft_isdigit(argv[i++]))
			return (0);
	return (1);
}

int			valid_positive_int(char *argv)
{
	long long	res;
	int			i;

	res = ft_atoi(argv);
	if (ft_strlen(argv) > 11 || res < 1 || res > 2147483647)
		return (0);
	i = 0;
	while (argv[i] != '\0')
		if ((argv[i] == '-' || argv[i] == '+') && i == 0 && ft_strlen(argv) > 1)
			i++;
		else if (!ft_isdigit(argv[i++]))
			return (0);
	return (1);
}
