/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 22:03:29 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/11 22:03:29 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path			*new_path(void)
{
	t_path		*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	path->rooms = NULL;
	path->length = 0;
	path->next = NULL;
	return (path);
}

int				add_path(t_path **paths, t_path *path)
{
	t_path		*tail;

	if (!paths || !path)
		return (0);
	tail = *paths;
	while (tail->next)
		tail = tail->next;
	tail->next = path;
	return (1);
}

void			free_last_path(t_path **paths)
{
	t_path		*tail;
	t_path		*tmp;

	if (!*paths)
		return ;
	tail = *paths;
	if (!tail->next)
	{
		free_path_rooms(&tail->rooms);
		free(tail);
		return ;
	}
	while (tail->next)
	{
		tmp = tail;
		tail = tail->next;
	}
	free_path_rooms(&tail->rooms);
	free(tail);
	tmp->next = NULL;
}

t_path_room		*new_path_room(t_vertex *room)
{
	t_path_room	*new_path_room;

	if (!(new_path_room = (t_path_room *)malloc(sizeof(t_path_room))))
		return (NULL);
	new_path_room->room = room;
	new_path_room->next = NULL;
	return (new_path_room);
}

int				push_path_room(t_path_room **path_rooms, t_path_room *path_room)
{
	if (!path_rooms || !path_room)
		return (0);
	if (*path_rooms)
		path_room->next = *path_rooms;
	*path_rooms = path_room;
	return (1);
}
