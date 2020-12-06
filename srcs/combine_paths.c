/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:39:27 by lseema            #+#    #+#             */
/*   Updated: 2020/12/04 23:46:15 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

//TODO: как?
int		find_common_links(t_lemin **lemin, t_path *path, short int **matrix)
{
	t_path		*new_paths;
	t_path		*temp;
	size_t		steps;

	if (!combine_paths(lemin, path, matrix))
	{
		add_path(&(*lemin)->paths, path);
		if ((steps = result_steps_count(lemin, &(*lemin)->paths)) >= (*lemin)->result_steps_count)
		{
			free_last_path(&(*lemin)->paths);
			steps = 0;
		}
	}
	else
	{
		new_paths = create_new_path(lemin, path, matrix);
		temp = (*lemin)->paths;
		while (temp)
		{
			add_path(&new_paths, create_new_path(lemin, temp, matrix));
			temp = (temp->next) ? temp->next : NULL;
		}
		free_paths(&path);
		if ((steps = result_steps_count(lemin, &new_paths)) >= (*lemin)->result_steps_count)
		{
			steps = 0;
			free_paths(&new_paths);
		}
		else
		{
			free_paths(&(*lemin)->paths);
			(*lemin)->paths = new_paths;
		}
	}
	return (steps);
}

t_path		*create_new_path(t_lemin **lemin, t_path *path, short int **matrix)
{
		t_path			*result;
		size_t			j;
		size_t			i;

		result = new_path();
		result->rooms = new_path_room((*lemin)->start_room);
		result->length++;
		add_path_room(&result->rooms, new_path_room(path->rooms->next->room));
		result->length++;
		i = path->rooms->next->room->index;
		while (i != (*lemin)->end_room->index)
		{
			j = 0;
			while (j < (*lemin)->rooms)
			{
				if (matrix[i][j] && j != result->rooms->room->index)
				{
					matrix[i][j] = 0;
					matrix[j][i] = 0;
					add_path_room(&result->rooms, new_path_room((*lemin)->adj[j]->room));
					i = j;
					result->length++;
					break;
				}
				j++;
			}
		}
		//add_path_room(&result->rooms, new_path_room((*lemin)->end_room));
		return result;
}

short int	combine_paths(t_lemin **lemin, t_path *path, short int **matrix)
{
	t_path 			*temp;
	t_path_room 	*path_rooms;
	short int		is_combine_arc;

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
		temp = (temp->next) ? temp->next : NULL;
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
	return is_combine_arc;
}

short int		**init_adj_matrix(t_lemin **lemin)
{
	size_t		i;
	size_t		j;
	short int	**matrix;

	i = 0;
	if (!(matrix = (short int **)malloc(sizeof(short int*) * (*lemin)->rooms)))
		return (NULL);
	while (i < (*lemin)->rooms)
	{
		if (!(matrix[i] = (short int *)malloc(sizeof(short int) * (*lemin)->rooms)))
			return (NULL);
		j = 0;
		while (j < (*lemin)->rooms)
			matrix[i][j++] = 0;
		i++;
	}
	return matrix;
}

void		free_adj_matrix(short int **matrix, size_t count)
{
	size_t i;

	i = 0;
	while (i < count)
		free(matrix[i++]);
	free(matrix);
}
