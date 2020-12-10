/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 22:43:34 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/10 22:37:26 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_all(t_lemin **lemin, t_line **lines, t_vertex **rooms)
{
	if (*lemin)
	{
		if ((*lemin)->rooms > 0 && (*lemin)->adj)
			free_adj((*lemin)->adj, (*lemin)->rooms);
		if ((*lemin)->paths)
			free_paths(&(*lemin)->paths);
		free(*lemin);
	}
	if (*lines)
		free_lines(lines);
	if (*rooms)
		free_rooms(rooms);
}

void			free_adj(t_adj **row, size_t count)
{
	size_t		i;

	i = 0;
	while (i < count)
	{
		free_links(&row[i]->links);
		free(row[i]);
		i++;
	}
	free(row);
}

int				free_str_arr(char **temp)
{
	size_t		i;

	i = 0;
	while (temp[i])
		free(temp[i++]);
	free(temp);
	return (0);
}

void			free_paths(t_path **paths)
{
	t_path		*tail;

	if (*paths)
	{
		tail = *paths;
		while (tail->next)
		{
			*paths = tail;
			free_path_rooms(&tail->rooms);
			tail = tail->next;
			free(*paths);
		}
		free_path_rooms(&tail->rooms);
		free(tail);
	}
}

void			free_path_rooms(t_path_room **path_rooms)
{
	t_path_room	*path_room;
	t_path_room	*temp;

	if (*path_rooms)
	{
		path_room = *path_rooms;
		while (path_room)
		{
			temp = path_room;
			path_room = path_room->next ? path_room->next : NULL;
			free(temp);
		}
	}
}
