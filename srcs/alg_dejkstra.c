/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_dejkstra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 20:33:18 by lseema            #+#    #+#             */
/*   Updated: 2020/12/01 20:51:10 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void	dejkstra_main(t_lemin **lemin, t_vertex **vertexes)
{
	t_vertex	*room;
	t_ilist		*neighbor;
	t_set		*set;
	t_set		*min_set;

	set = NULL;
	dejkstra_init(vertexes, lemin);
	room = (*lemin)->start_room;
	while (room && room != (*lemin)->end_room)
	{
		neighbor = (*lemin)->adj[room->index]->links;
		while (neighbor)
		{
			if (!neighbor->is_blocked && room->distance + neighbor->weight < (*lemin)->adj[neighbor->index]->room->distance)
			{
				if ((*lemin)->start_room != room && room->splited && find_link_by_index(&(*lemin)->adj[room->parent_index]->links, room->index)->weight != -1)
				{
					if (neighbor->weight == -1)
					{
						(*lemin)->adj[neighbor->index]->room->distance = room->distance + neighbor->weight;
						(*lemin)->adj[neighbor->index]->room->parent_index = room->index;
						if (!is_contain_in_set(&set, neighbor->index))
						{
							if (!set)
								set = new_set_elem((*lemin)->adj[neighbor->index]->room);
							else
								add_to_set(&set, new_set_elem((*lemin)->adj[neighbor->index]->room));
						}
					}
				}
				else
				{
					(*lemin)->adj[neighbor->index]->room->distance = room->distance + neighbor->weight;
					(*lemin)->adj[neighbor->index]->room->parent_index = room->index;
					if (!is_contain_in_set(&set, neighbor->index))
					{
						if (!set)
							set = new_set_elem((*lemin)->adj[neighbor->index]->room);
						else
							add_to_set(&set, new_set_elem((*lemin)->adj[neighbor->index]->room));
					}
				}
			}
			if (neighbor->next)
				neighbor = neighbor->next;
			else
				break;
		}
		min_set = find_min_in_set(&set);
		room = min_set ? min_set->room : NULL;
		if (min_set)
			remove_in_set(&set, min_set);
	}
	free_set(&set);
}

void	dejkstra_init(t_vertex **vertexes, t_lemin **lemin)
{
	size_t		i;
	t_vertex	*rooms;

	i = 0;
	rooms = *vertexes;
	while (rooms->next)
	{
		rooms->distance = SIZE_MAX;
		rooms->parent_index = SIZE_MAX;
		rooms = rooms->next;
	}
	rooms->distance = SIZE_MAX;
	rooms->parent_index = SIZE_MAX;
	(*lemin)->start_room->distance = 0;
}
