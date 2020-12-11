/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_suurballe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 23:29:16 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/10 22:37:30 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			suurballe_main(t_lemin **lemin, t_vertex **rooms, size_t steps)
{
	t_path		*new_path;
	short int	**adj_matrix;

	while ((size_t)(*lemin)->ants > (*lemin)->paths_count && steps)
	{
		init_rooms(lemin, rooms);
		split_rooms_on_paths(lemin);
		dejkstra_main(lemin, rooms);
		if (!(new_path = reverse_finded_path(lemin)))
			return ;
		if (!(*lemin)->paths_count)
		{
			(*lemin)->paths = new_path;
			steps = result_steps_count(lemin, &(*lemin)->paths);
		}
		else
		{
			if (!(adj_matrix = init_adj_matrix(lemin)))
				return ;
			steps = find_common_links(lemin, new_path, adj_matrix);
			free_adj_matrix(adj_matrix, (*lemin)->rooms);
		}
		if (steps > 0)
		{
			(*lemin)->paths_count++;
			(*lemin)->result_steps_count = steps;
		}
	}
}

void			init_rooms(t_lemin **lemin, t_vertex **rooms)
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

void			split_and_set_weight(t_path_room **path_rooms, t_lemin **lemin)
{
	t_path_room	*path_room;

	path_room = *path_rooms;
	while (path_room->next)
	{
		if (path_room->room != (*lemin)->start_room)
			path_room->room->splited = 1;
		find_link_by_index(&(*lemin)->adj[path_room->room->index]->links,
			path_room->next->room->index)->is_blocked = 1;
		find_link_by_index(&(*lemin)->adj[path_room->next->room->index]->links,
			path_room->room->index)->weight = -1;
		path_room = path_room->next;
	}
}

void		free_adj_matrix(short int **matrix, size_t count)
{
	size_t i;

	i = 0;
	while (i < count)
		free(matrix[i++]);
	free(matrix);
}
