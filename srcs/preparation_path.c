/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:28:57 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/12 19:28:57 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path			*reverse_finded_path(t_lemin **lemin)
{
	t_vertex	*curr_room;
	t_path		*path;

	if ((*lemin)->end_room->distance == SIZE_MAX || !(path = new_path()))
		return (NULL);
	path->rooms = new_path_room((*lemin)->end_room);
	curr_room = (*lemin)->adj[(*lemin)->end_room->parent_index]->room;
	path->length = 1;
	while (curr_room != (*lemin)->start_room)
	{
		push_path_room(&path->rooms, new_path_room(curr_room));
		curr_room = (*lemin)->adj[curr_room->parent_index]->room;
		path->length++;
	}
	push_path_room(&path->rooms, new_path_room((*lemin)->start_room));
	path->length++;
	return (path);
}

size_t			result_steps_count(t_lemin **lemin, t_path **paths)
{
	size_t		steps;
	size_t		i;
	size_t		lengths[(*lemin)->paths_count + 1];
	int			koef[(*lemin)->paths_count + 1];
	int			ants;

	steps = 0;
	i = 0;
	ants = (*lemin)->ants;
	get_sorted_paths_lengths(lengths, (*lemin)->paths_count + 1, paths, NULL);
	calc_koefs(koef, (*lemin)->paths_count + 1, lengths);
	while (ants)
	{
		i = 0;
		steps++;
		while (i < (*lemin)->paths_count + 1)
		{
			if (ants > koef[i])
				ants--;
			if (!ants)
				break ;
			i++;
		}
	}
	return (steps + (lengths[i] - 1) - 1);
}

void			get_sorted_paths_lengths(size_t lens[],
	size_t path_count, t_path **paths, t_vertex **path_with_idexes)
{
	size_t		i;
	t_path		*path;

	i = 0;
	path = *paths;
	while (i < path_count)
	{
		lens[i++] = path->length;
		if (path->next)
			path = path->next;
	}
	insert_sort_mod(lens, path_count, path_with_idexes, 0);
}

void			insert_sort_mod(size_t arr[], size_t n,
								t_vertex **paths, size_t i)
{
	size_t		j;
	size_t		min_idx;
	size_t		temp;
	t_vertex	*temp_vertex;

	while (i < n - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < n)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
			j++;
		}
		temp = arr[min_idx];
		arr[min_idx] = arr[i];
		arr[i++] = temp;
		if (paths)
		{
			temp_vertex = paths[min_idx];
			paths[min_idx] = paths[--i];
			paths[i++] = temp_vertex;
		}
	}
}

void			calc_koefs(int koef[], size_t count, size_t lengths[])
{
	size_t		i;
	size_t		j;

	j = 0;
	while (j < count)
	{
		i = 0;
		koef[j] = 0;
		while (i < j)
		{
			koef[j] += (lengths[j] - 1) - (lengths[i] - 1);
			i++;
		}
		j++;
	}
}
