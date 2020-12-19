/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:27:54 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 15:31:46 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				print_error(void)
{
	ft_putendl_fd("ERROR", 2);
	return (0);
}

int				main(void)
{
	t_lemin		*lemin;
	t_line		*lines;
	t_vertex	*rooms;
	t_vertex	**paths;

	rooms = NULL;
	lines = NULL;
	if (!init_lemin(&lemin)
		|| (parse_lines(&lines, &lemin, &rooms)) < 6
		|| !lemin->links)
	{
		free_all(&lemin, &lines, &rooms);
		return (print_error());
	}
	suurballe_main(&lemin, &rooms, 1);
	if (!lemin->paths_count)
	{
		free_all(&lemin, &lines, &rooms);
		return (print_error());
	}
	print_lines(&lines, lemin->do_color);
	paths = indexing_paths(&lemin, 0, 0);
	ants_go(&lemin, paths, lemin->ants, 0);
	free_all(&lemin, &lines, &rooms);
	return (0);
}

int				init_lemin(t_lemin **lemin)
{
	if (!(*lemin = (t_lemin*)malloc(sizeof(t_lemin))))
		return (0);
	(*lemin)->ants = 0;
	(*lemin)->step = ANT;
	(*lemin)->next_is_end = FALSE;
	(*lemin)->next_is_start = FALSE;
	(*lemin)->do_color = FALSE;
	(*lemin)->links = 0;
	(*lemin)->rooms = 0;
	(*lemin)->paths_count = 0;
	(*lemin)->result_steps_count = 0;
	(*lemin)->start_room = NULL;
	(*lemin)->end_room = NULL;
	(*lemin)->adj = NULL;
	(*lemin)->paths = NULL;
	return (1);
}

t_vertex		**indexing_paths(t_lemin **lemin, size_t i, size_t j)
{
	t_vertex	**indexed_paths;
	t_path		*path;
	t_path_room	*path_room;

	indexed_paths = (t_vertex **)malloc(sizeof(t_vertex *)
		* (*lemin)->paths_count);
	path = (*lemin)->paths;
	while (i < (*lemin)->paths_count)
	{
		indexed_paths[i] = (t_vertex *)malloc(sizeof(t_vertex) * path->length);
		j = 0;
		path_room = path->rooms;
		while (j < path->length)
		{
			indexed_paths[i][j] = *path_room->room;
			j++;
			path_room = path_room->next;
		}
		i++;
		path = path->next;
	}
	return (indexed_paths);
}
