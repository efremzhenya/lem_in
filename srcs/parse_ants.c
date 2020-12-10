/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 19:46:06 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/10 22:37:26 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		parse_ants(char *line, t_lemin **lemin)
{
	if (ft_strlen(line) > 11 || !valid_positive_int(line))
		return (0);
	else
		(*lemin)->ants = ft_atoi(line);
	(*lemin)->step++;
	return (1);
}
