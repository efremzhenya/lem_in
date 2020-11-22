/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:41:41 by lseema            #+#    #+#             */
/*   Updated: 2020/11/22 20:11:02 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int		print_error()
{
	ft_putendl_fd("ERROR", 2);
	return (0);
}

int		init_lemin(t_lemin **lemin)
{
	if (!(*lemin = (t_lemin*)malloc(sizeof(t_lemin))))
		return (0);
	(*lemin)->ants = 0;
	(*lemin)->step = 0;
	(*lemin)->next_is_end = 0;
	(*lemin)->next_is_start = 0;
	(*lemin)->links = 0;
	(*lemin)->rooms = 0;
	(*lemin)->lines = 0;
	(*lemin)->start_room = NULL;
	(*lemin)->end_room = NULL;
	(*lemin)->adj = NULL;
	(*lemin)->bfs_queue = NULL;
	return (1);
}

void	print_adj_list(t_lemin **lemin)
{
	size_t i;
	t_ilist *list;

	i = 0;
	if ((*lemin)->rooms > 0)
	{
		while (i < ((*lemin)->rooms))
		{
			ft_putnbr((*lemin)->adj[i]->index);
			if ((*lemin)->adj[i]->links)
			{
				write(1, ": ", 2);
				list = (*lemin)->adj[i]->links;
				while (list->next)
				{
					ft_putnbr(list->index);
					write(1, ", ", 2);
					list = list->next;
				}
				ft_putnbr(list->index);
			}
			write(1, "\n", 1);
			i++;
		}
	}
}

int		main()
{
	t_lemin		*lemin;
	t_line		*lines;
	t_vertex	*rooms;

	rooms = NULL;
	lines = NULL;
	if (!init_lemin(&lemin)
		|| (lemin->lines = parse_lines(&lines, &lemin, &rooms)) < 6
		|| !lemin->links || !new_queue(&lemin->bfs_queue))
	{
		free_all(&lemin, &lines, &rooms);
		return print_error();
	}
	bfs(&lemin);
	print_lines(&lines);
	print_adj_list(&lemin);
	free_all(&lemin, &lines, &rooms);
	return (0);
}
