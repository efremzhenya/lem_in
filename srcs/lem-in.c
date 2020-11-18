/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:41:41 by lseema            #+#    #+#             */
/*   Updated: 2020/11/19 00:08:57 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int		print_error()
{
	ft_putendl_fd("ERROR", 2);
	return (0);
}

int		main()
{
	t_lemin *lemin;

	if (!(lemin = (t_lemin*)malloc(sizeof(t_lemin))))
		return print_error();
	parse(&lemin);
	return (0);
}
