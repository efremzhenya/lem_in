/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 15:21:14 by lseema            #+#    #+#             */
/*   Updated: 2020/12/06 01:16:57 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

t_path		*reverse_finded_path(t_lemin **lemin)
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

//TODO: тестируй
size_t		result_steps_count(t_lemin **lemin, t_path **paths)
{
	size_t		steps;
	size_t		i;
	size_t		lengths[(*lemin)->paths_count + 1];
	int			koef[(*lemin)->paths_count + 1];
	int			ants;

	steps = 0;
	ants = (*lemin)->ants;
	get_array_of_paths_lengths(lengths, (*lemin)->paths_count + 1, paths);
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
				break;
			i++;
		}
	}
	return steps += (lengths[i] - 1) - 1;
}

void		get_array_of_paths_lengths(size_t lengths[], size_t path_count, t_path **paths)
{
	size_t	i;
	t_path	*path;

	i = 0;
	path = *paths;
	while (i < path_count)
	{
		lengths[i++] = path->length;
		if (path->next)
			path = path->next;
	}
	insertionSort(lengths, path_count);
}

void insertionSort(size_t arr[], size_t n)
{
    size_t i, j, min_idx;
	size_t temp = 0;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        // Swap the found minimum element with the first element
		temp = arr[min_idx];
		arr[min_idx] = arr[i];
		arr[i] = temp;
    }
}

void		sort_paths_and_lengths(size_t lengths[], size_t path_count, t_path **paths, t_vertex **path_with_idexes)
{
	size_t	i;
	t_path	*path;

	i = 0;
	path = *paths;
	while (i < path_count)
	{
		lengths[i++] = path->length;
		if (path->next)
			path = path->next;
	}
	insertionSort_two_array(lengths, path_count, path_with_idexes);
}

void		insertionSort_two_array(size_t arr[], size_t n, t_vertex **paths)
{
    size_t i, j, min_idx;
	size_t temp = 0;
	t_vertex *temp_vertex;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        // Swap the found minimum element with the first element
		temp = arr[min_idx];
		temp_vertex = paths[min_idx];
		arr[min_idx] = arr[i];
		paths[min_idx] = paths[i];
		arr[i] = temp;
		paths[i] = temp_vertex;
    }
}

void	calc_koefs(int koef[], size_t count, size_t lengths[])
{
	size_t	i;
	size_t 	j;

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
