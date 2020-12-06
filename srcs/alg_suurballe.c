/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_suurballe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 20:33:22 by lseema            #+#    #+#             */
/*   Updated: 2020/12/02 22:55:40 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void		suurballe_main(t_lemin **lemin, t_vertex **rooms)
{
	t_path		*path;
	size_t 		steps;
	short int	**adj_matrix;

	while ((size_t)(*lemin)->ants > (*lemin)->paths_count)
	{
		init_rooms(lemin, rooms);
		split_rooms_on_paths(lemin);
		dejkstra_main(lemin, rooms);
		if (!(path = reverse_finded_path(lemin)))
			return ;
		if (!(*lemin)->paths_count)
		{
			(*lemin)->paths = path;
			steps = result_steps_count(lemin, &(*lemin)->paths);
		}
		else
		{
			if (!(adj_matrix = init_adj_matrix(lemin)))
				return ;
			steps = find_common_links(lemin, path, adj_matrix);
			free_adj_matrix(adj_matrix, (*lemin)->rooms);
		}
		if (steps > 0)
		{
			(*lemin)->paths_count++;
			(*lemin)->result_steps_count = steps;
		}
		else
			return;
	}
}

void		init_rooms(t_lemin **lemin, t_vertex **rooms)
{
	t_vertex	*vertex;
	size_t		i;
	t_ilist		*link;

	vertex = *rooms;
	while (vertex)
	{
		vertex->splited = 0;
		vertex = vertex->next ? vertex->next : NULL;
	}
	i = 0;
	while (i < (*lemin)->rooms)
	{
		link = (*lemin)->adj[i++]->links;
		while (link)
		{
			link->is_blocked = 0;
			link->weight = 1;
			link = link->next ? link->next : NULL;
		}
	}
}

void		split_rooms_on_paths(t_lemin **lemin)
{
	t_path	*path;

	if (!(*lemin)->paths_count)
		return ;
	path = (*lemin)->paths;
	while (path->next)
	{
		split_and_set_weight(&path->rooms, lemin);
		path = path->next;
	}
	split_and_set_weight(&path->rooms, lemin);
}

void		split_and_set_weight(t_path_room **path_rooms, t_lemin **lemin)
{
	t_path_room *path_room;

	path_room = *path_rooms;
	while (path_room->next)
	{
		if (path_room->room != (*lemin)->start_room)
			path_room->room->splited = 1;
		find_link_by_index(&(*lemin)->adj[path_room->room->index]->links, path_room->next->room->index)->is_blocked = 1;
		find_link_by_index(&(*lemin)->adj[path_room->next->room->index]->links, path_room->room->index)->weight = -1;
		path_room = path_room->next;
	}
}

