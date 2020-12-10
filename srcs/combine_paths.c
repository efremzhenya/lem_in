/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:39:27 by lseema            #+#    #+#             */
/*   Updated: 2020/12/10 23:32:56 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path		*create_new_path(t_lemin **lemin, t_path *path,
					short int **matrix, size_t index)
{
	t_path			*r;
	size_t			j;

	r = new_path();
	r->rooms = new_path_room((*lemin)->start_room);
	add_path_room(&r->rooms, new_path_room(path->rooms->next->room));
	r->length = 2;
	while (index != (*lemin)->end_room->index)
	{
		j = 0;
		while (j < (*lemin)->rooms)
		{
			if (matrix[index][j] && j != r->rooms->room->index)
			{
				matrix[index][j] = 0;
				matrix[j][index] = 0;
				add_path_room(&r->rooms, new_path_room((*lemin)->adj[j]->room));
				index = j;
				r->length++;
				break ;
			}
			j++;
		}
	}
	return (r);
}

short int	combine_paths(t_lemin **lemin, t_path *path, short int **matrix)
{
	t_path		*temp;
	t_path_room	*path_rooms;
	short int	is_combine_arc;

	is_combine_arc = 0;
	temp = (*lemin)->paths;
	while (temp)
	{
		path_rooms = temp->rooms;
		while (path_rooms->next)
		{
			matrix[path_rooms->room->index][path_rooms->next->room->index] = 1;
			matrix[path_rooms->next->room->index][path_rooms->room->index] = 1;
			path_rooms = path_rooms->next;
		}
		temp = temp->next;
	}
	path_rooms = path->rooms;
	while (path_rooms->next)
	{
		matrix[path_rooms->room->index][path_rooms->next->room->index] =
			!matrix[path_rooms->room->index][path_rooms->next->room->index];
		matrix[path_rooms->next->room->index][path_rooms->room->index] =
			!matrix[path_rooms->next->room->index][path_rooms->room->index];
		if (!matrix[path_rooms->room->index][path_rooms->next->room->index])
			is_combine_arc++;
		path_rooms = path_rooms->next;
	}
	return (is_combine_arc);
}

short int	**init_adj_matrix(t_lemin **lemin)
{
	size_t		i;
	size_t		j;
	short int	**matrix;

	i = 0;
	if (!(matrix = malloc(sizeof(short int*) * (*lemin)->rooms)))
		return (NULL);
	while (i < (*lemin)->rooms)
	{
		if (!(matrix[i] = malloc(sizeof(short int) * (*lemin)->rooms)))
			return (NULL);
		j = 0;
		while (j < (*lemin)->rooms)
			matrix[i][j++] = 0;
		i++;
	}
	return (matrix);
}
