/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:41:41 by lseema            #+#    #+#             */
/*   Updated: 2020/11/18 21:08:08 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int		print_error()
{
	ft_putendl_fd("ERROR", 2);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc > 2)
	{
		validate(argv);
	}
	return (0);
}
