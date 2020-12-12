/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:27:18 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/12 19:27:18 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ants_init(t_ant **ants, int count)
{
	int			i;

	i = 0;
	while (i < count)
	{
		ants[i] = (t_ant*)malloc(sizeof(t_ant));
		ants[i]->path_index = 0;
		ants[i]->room_index = 1;
		ants[i++]->is_active = FALSE;
	}
}

void			free_ants(t_lemin **lemin, t_ant **ants, t_vertex **paths)
{
	size_t		i;

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

void			ants_go(t_lemin **lemin, t_vertex **paths, int ants, size_t i)
{
	size_t		lengths[(*lemin)->paths_count];
	int			koef[(*lemin)->paths_count];
	t_ant		**ants_info;

	ants_info = (t_ant **)malloc(sizeof(t_ant*) * (*lemin)->ants);
	ants_init(ants_info, (*lemin)->ants);
	get_sorted_paths_lengths(
		lengths, (*lemin)->paths_count, &(*lemin)->paths, paths);
	calc_koefs(koef, (*lemin)->paths_count, lengths);
	while (move_ants(lemin, ants_info, paths, 0) || ants)
	{
		i = 0;
		while (i < (*lemin)->paths_count && ants)
		{
			if (ants > koef[i])
			{
				ants_info[(*lemin)->ants - ants]->path_index = i;
				ants_info[(*lemin)->ants - ants--]->is_active = TRUE;
			}
			if (!ants)
				break ;
			i++;
		}
	}
	free_ants(lemin, ants_info, paths);
}

int				move_ants(t_lemin **lemin, t_ant **ants,
							t_vertex **paths, int i)
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
			write(1, "L", 1);
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
