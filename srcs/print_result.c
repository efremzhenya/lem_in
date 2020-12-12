/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:29:03 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/12 19:29:03 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_lines(t_line **lines)
{
	t_line *tail;

	tail = *lines;
	while (tail && tail->next)
	{
		ft_putstr(tail->value);
		write(1, "\n", 1);
		tail = tail->next;
	}
	if (tail)
	{
		ft_putstr(tail->value);
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
}
