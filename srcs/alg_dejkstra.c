/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_dejkstra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 23:22:01 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/08 19:21:23 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		adjacent_if_satisfy(t_lemin ***lemin, t_vertex **room,
									t_ilist **neighbor, t_set **set)
{
	if ((*(*lemin))->start_room != *room && (*room)->splited &&
		find_link_by_index(&(**lemin)->adj[(*room)->parent_index]->links,
				(*room)->index)->weight != -1)
	{
		if ((*neighbor)->weight == -1)
		{
			(*(*lemin))->adj[(*neighbor)->index]->room->distance =
					(*room)->distance + (*neighbor)->weight;
			(*(*lemin))->adj[(*neighbor)->index]->room->parent_index =
					(*room)->index;
			if (!is_contain_in_set(&(*set), (*neighbor)->index))
			{
				if (!(*set))
					*set = new_set_elem((*(*lemin))->
							adj[(*neighbor)->index]->room);
				else
					add_to_set(&(*set), new_set_elem((*(*lemin))->
					adj[(*neighbor)->index]->room));
			}
		}
		return (TRUE);
	}
	return (FALSE);
}

static void		adjacent_if_not(t_lemin ***lemin, t_vertex **room,
		t_ilist **neighbor, t_set **set)
{
	(*(*lemin))->adj[(*neighbor)->index]->room->distance =
			(*room)->distance + (*neighbor)->weight;
	(*(*lemin))->adj[(*neighbor)->index]->room->parent_index = (*room)->index;
	if (!is_contain_in_set(&(*set), (*neighbor)->index))
	{
		if (!(*set))
			*set = new_set_elem((*(*lemin))->adj[(*neighbor)->index]->room);
		else
			add_to_set(&(*set), new_set_elem((*(*lemin))->
			adj[(*neighbor)->index]->room));
	}
}

void			dejkstra_main(t_lemin **lemin, t_vertex **vertexes)
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
			if (!neighbor->is_blocked && room->distance + neighbor->weight
				< (*lemin)->adj[neighbor->index]->room->distance)
				if (!adjacent_if_satisfy(&lemin, &room, &neighbor, &set))
					adjacent_if_not(&lemin, &room, &neighbor, &set);
			neighbor = neighbor->next;
		}
		min_set = find_min_in_set(&set);
		room = min_set ? min_set->room : NULL;
		if (min_set)
			remove_in_set(&set, min_set);
	}
	free_set(&set);
}

void			dejkstra_init(t_vertex **vertexes, t_lemin **lemin)
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
