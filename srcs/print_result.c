/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:29:03 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 16:03:18 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_lines(t_line **lines, int do_color)
{
	t_line	*tail;

	tail = *lines;
	while (tail)
	{
		if (*(tail->value) == '#' && do_color)
		{
			ft_putstr("\x1B[36m");
			ft_putstr(tail->value);
			write(1, "\n", 1);
			ft_putstr("\x1B[0m");
			tail = tail->next;
		}
		else
		{
			ft_putstr(tail->value);
			write(1, "\n", 1);
			tail = tail->next;
		}
	}
	write(1, "\n", 1);
}

void		print_ant(int which, int do_color)
{
	if (do_color)
	{
		ft_putstr("\x1B[35m");
		write(1, "L", 1);
		ft_putnbr(which);
		ft_putstr("\x1B[0m");
	}
	else
	{
		write(1, "L", 1);
		ft_putnbr(which);
	}
}

void		print_room(char *which, char *finish, int do_color)
{
	if (do_color)
	{
		if (ft_strequ(which, finish))
		{
			ft_putstr("\x1B[34m");
			ft_putstr(which);
			ft_putstr("\x1B[0m");
		}
		else
		{
			ft_putstr("\x1B[33m");
			ft_putstr(which);
			ft_putstr("\x1B[0m");
		}
	}
	else
		ft_putstr(which);
}
