/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:32:43 by lseema            #+#    #+#             */
/*   Updated: 2020/11/19 00:09:48 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

char	*read_next_line()
{
	char	*line;

	line = NULL;
	return get_next_line(0, &line) > 0 ? line : NULL;
}

int		parse(t_lemin **lemin)
{
	if (!parse_ants(lemin, read_next_line()))
		return (0);
	return(1);
}

int		parse_ants(t_lemin **lemin, char *line)
{
	if (!*line)
		return (0);
	if (ft_strlen(line) > 10 || !validate_positive_num(line))
	{
		free(line);
		return(0);
	}
	else
	{
		(*lemin)->ants_count = ft_atoi(line);
		free(line);
		return(1);
	}
}

int		validate_positive_num(char *argv)
{
	long long	res;
	int			i;

	res = ft_atoi(argv);
	if (ft_strlen(argv) > 10 || res < 1 || res > 2147483647)
		return (0);
	i = 0;
	while (argv[i] != '\0')
		if (argv[i] == '-' && i == 0 && ft_strlen(argv) > 1)
			i++;
		else if (!ft_isdigit(argv[i++]))
			return (0);
	return (1);
}
