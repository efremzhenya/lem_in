/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 04:36:33 by lseema            #+#    #+#             */
/*   Updated: 2020/12/06 18:03:05 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
