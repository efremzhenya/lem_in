/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:41:41 by lseema            #+#    #+#             */
/*   Updated: 2020/12/06 16:18:40 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int		print_error()
{
	ft_putendl_fd("ERROR", 2);
	return (0);
}

int		init_lemin(t_lemin **lemin)
{
	if (!(*lemin = (t_lemin*)malloc(sizeof(t_lemin))))
		return (0);
	(*lemin)->ants = 0;
	(*lemin)->step = ANT;
	(*lemin)->next_is_end = FALSE;
	(*lemin)->next_is_start = FALSE;
	(*lemin)->links = 0;
	(*lemin)->rooms = 0;
	(*lemin)->lines = 0;
	(*lemin)->routes = 0;
	(*lemin)->paths_count = 0;
	(*lemin)->result_steps_count = 0;
	(*lemin)->start_room = NULL;
	(*lemin)->end_room = NULL;
	(*lemin)->adj = NULL;
	(*lemin)->bfs_queue = NULL;
	(*lemin)->paths = NULL;
	(*lemin)->set = NULL;
	(*lemin)->need_free_paths = 0;
	return (1);
}

int		main()
{
	t_lemin		*lemin;
	t_line		*lines;
	t_vertex	*rooms;
	t_vertex	**paths;

	rooms = NULL;
	lines = NULL;
	if (!init_lemin(&lemin)
		|| (lemin->lines = parse_lines(&lines, &lemin, &rooms)) < 6
		|| !lemin->links)
	{
		free_all(&lemin, &lines, &rooms);
		return print_error();
	}
	suurballe_main(&lemin, &rooms);
	if (!lemin->paths_count)
	{
		free_all(&lemin, &lines, &rooms);
		return print_error();
	}
	print_lines(&lines);
	paths = indexing_paths(&lemin, 0, 0);
	ants_go(&lemin, paths, lemin->ants, 0);
	free_all(&lemin, &lines, &rooms);
	return (0);
}

t_vertex	**indexing_paths(t_lemin **lemin, size_t i, size_t j)
{
	t_vertex	**indexed_paths;
	t_path		*path;
	t_path_room	*path_room;

	indexed_paths = (t_vertex **)malloc(sizeof(t_vertex *) * (*lemin)->paths_count);
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
	return indexed_paths;
}

void		ants_go(t_lemin **lemin, t_vertex **paths, int ants, size_t i)
{
	size_t	lengths[(*lemin)->paths_count];
	int		koef[(*lemin)->paths_count];
	t_ant	**ants_info;

	ants_info = (t_ant **)malloc(sizeof(t_ant*) * (*lemin)->ants);
	ants_init(ants_info, (*lemin)->ants);
	sort_paths_and_lengths(lengths, (*lemin)->paths_count, &(*lemin)->paths, paths);
	calc_koefs(koef, (*lemin)->paths_count, lengths);
	while (move_ants(lemin, ants_info, paths, 0) || ants)
	{
		i = 0;
		while (i < (*lemin)->paths_count && ants)
		{
			if (ants > koef[i])
			{
				ants_info[(*lemin)->ants - ants]->path_index = i;
				ants_info[(*lemin)->ants - ants]->is_active = TRUE;
				ants--;
			}
			if (!ants)
				break;
			i++;
		}
	}
	free_ants(lemin, ants_info, paths);
}

void	free_ants(t_lemin **lemin, t_ant **ants, t_vertex **paths)
{
	size_t i;

	i = 0;
	if (*ants)
	{
		while (i < (size_t)(*lemin)->ants)
			free(ants[i++]);
		free(ants);
	}
	i = 0;
	if (*paths)
	{
		while (i < (*lemin)->paths_count)
			free(paths[i++]);
		free(paths);
	}
}

void		ants_init(t_ant **ants, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		ants[i] = (t_ant*)malloc(sizeof(t_ant));
		ants[i]->path_index = 0;
		ants[i]->room_index = 1;
		ants[i++]->is_active = FALSE;
	}
}

int			move_ants(t_lemin **lemin, t_ant **ants, t_vertex **paths, int i)
{
	short int	is_any_move;

	is_any_move = FALSE;
	while (i < (*lemin)->ants)
	{
		if (ants[i]->is_active)
		{
			if (is_any_move)
				write(1, " ", 1);
			else
				is_any_move = TRUE;
			write(1, "L" , 1);
			ft_putnbr(i);
			write(1, "-", 1);
			ft_putstr(paths[ants[i]->path_index][ants[i]->room_index].name);
			if ((*lemin)->end_room->index ==
				paths[ants[i]->path_index][ants[i]->room_index++].index)
				ants[i]->is_active = FALSE;
		}
		i++;
	}
	if (is_any_move)
		write(1, "\n", 1);
	return (is_any_move);
}
