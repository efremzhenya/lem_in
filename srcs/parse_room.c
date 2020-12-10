/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 20:13:27 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/10 22:37:26 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				parse_room_type(char *line, t_lemin **lemin, t_vertex **rooms)
{
	if ((*lemin)->next_is_start)
	{
		if (parse_room(line, lemin, rooms))
			(*lemin)->start_room = get_last_added(rooms);
		(*lemin)->next_is_start = FALSE;
		return ((*lemin)->start_room != NULL);
	}
	else if ((*lemin)->next_is_end)
	{
		if (parse_room(line, lemin, rooms))
			(*lemin)->end_room = get_last_added(rooms);
		(*lemin)->next_is_end = FALSE;
		return ((*lemin)->end_room != NULL);
	}
	else if (!ft_strcmp(line, "##start"))
		return ((*lemin)->next_is_start = (*lemin)->start_room == NULL
		&& !(*lemin)->next_is_start && !(*lemin)->next_is_end);
	else if (!ft_strcmp(line, "##end"))
		return ((*lemin)->next_is_end = ((*lemin)->end_room == NULL
		&& !(*lemin)->next_is_start && !(*lemin)->next_is_end));
	else
		return (parse_room(line, lemin, rooms));
}

int				parse_room(char *line, t_lemin **lemin, t_vertex **rooms)
{
	char		**parts;
	int			x;
	int			y;

	if (ft_chrcount(line, ' ') != 2 || ft_chrcount(line, '-'))
		return (0);
	parts = ft_strsplit(line, ' ');
	if (!valid_int(parts[1]) || !valid_int(parts[2]))
		return (free_str_arr(parts));
	x = ft_atoi(parts[1]);
	y = ft_atoi(parts[2]);
	if (is_room_dup(rooms, parts[0], x, y))
		return (free_str_arr(parts));
	if (!*rooms)
		*rooms = new_vertex(ft_strdup(parts[0]), (*lemin)->rooms++, x, y);
	else
		add_vertex(
			rooms, new_vertex(ft_strdup(parts[0]), (*lemin)->rooms++, x, y));
	free_str_arr(parts);
	return (1);
}

void			free_rooms(t_vertex **rooms)
{
	t_vertex	*tail;

	if (*rooms)
	{
		tail = *rooms;
		while (tail->next)
		{
			*rooms = tail;
			tail = tail->next;
			free((*rooms)->name);
			free(*rooms);
		}
		free(tail->name);
		free(tail);
	}
}
