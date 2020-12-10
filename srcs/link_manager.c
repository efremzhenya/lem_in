/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 22:37:45 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/10 23:36:46 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	count_common_path(t_lemin ***lemin, t_path *path,
								short **matrix, size_t *steps)
{
	t_path	*new_paths;
	t_path	*temp;

	new_paths = create_new_path(*lemin, path,
			matrix, path->rooms->next->room->index);
	temp = (*(*lemin))->paths;
	while (temp)
	{
		add_path(&new_paths, create_new_path(*lemin, temp,
				matrix, temp->rooms->next->room->index));
		temp = temp->next;
	}
	free_paths(&path);
	if ((*steps = result_steps_count(*lemin, &new_paths)) >=
		(*(*lemin))->result_steps_count)
	{
		*steps = 0;
		free_paths(&new_paths);
	}
	else
	{
		free_paths(&(*(*lemin))->paths);
		(*(*lemin))->paths = new_paths;
	}
}

int			find_common_links(t_lemin **lemin, t_path *path, short int **matrix)
{
	size_t		steps;

	if (!combine_paths(lemin, path, matrix))
	{
		add_path(&(*lemin)->paths, path);
		if ((steps = result_steps_count(lemin, &(*lemin)->paths)) >=
			(*lemin)->result_steps_count)
		{
			free_last_path(&(*lemin)->paths);
			steps = 0;
		}
	}
	else
		count_common_path(&lemin, path, matrix, &steps);
	return (steps);
}
