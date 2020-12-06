/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:47:47 by lseema            #+#    #+#             */
/*   Updated: 2020/12/06 18:02:41 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		parse_ants(char *line, t_lemin **lemin)
{
	if (ft_strlen(line) > 11 || !valid_positive_int(line))
		return (0);
	else
		(*lemin)->ants = ft_atoi(line);
	(*lemin)->step++;
	return (1);
}
