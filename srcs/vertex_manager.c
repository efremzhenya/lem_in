/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 02:13:50 by lseema            #+#    #+#             */
/*   Updated: 2020/12/01 21:30:32 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

t_vertex	*new_vertex(char *name, size_t index, int x, int y)
{
	t_vertex *vertex;

	if (!(vertex = (t_vertex *)malloc(sizeof(t_vertex))))
		return (NULL);
	vertex->name = name;
	vertex->index = index;
	vertex->x = x;
	vertex->y = y;
	vertex->splited = 0;
	vertex->next = NULL;
	vertex->prev = NULL;
	return (vertex);
}

int		add_vertex(t_vertex **rooms, t_vertex *vertex)
{
	t_vertex	*tail;

	if (!rooms || !vertex)
		return (0);
	tail = *rooms;
	while (tail->next)
		tail = tail->next;
	tail->next = vertex;
	vertex->next = NULL;
	vertex->prev = tail;
	return (1);
}

int		is_room_dup(t_vertex **rooms, char *name, int x, int y)
{
	t_vertex	*tail;

	if (!rooms || !*rooms)
		return (0);
	tail = *rooms;
	while (tail->next)
	{
		if (!ft_strcmp(tail->name, name) || (tail->x == x && tail->y == y))
			return (1);
		tail = tail->next;
	}
	return (!ft_strcmp(tail->name, name) || (tail->x == x && tail->y == y));
}

int		is_room_contain(t_vertex **rooms, char *name)
{
	t_vertex	*tail;

	if (!rooms || !*rooms)
		return (0);
	tail = *rooms;
	while (tail->next)
	{
		if (!ft_strcmp(name, tail->name))
			return (1);
		tail = tail->next;
	}
	return (!ft_strcmp(name, tail->name));
}

size_t		get_room_index(char *name, t_vertex **rooms)
{
	t_vertex	*tail;

	if (!rooms)
		return (-1);
	tail = *rooms;
	while (tail->next)
	{
		if (!ft_strcmp(name, tail->name))
			return (tail->index);
		tail = tail->next;
	}
	if (!ft_strcmp(name, tail->name))
		return (tail->index);
	return (-1);
}

t_vertex	*get_last_added(t_vertex **rooms)
{
	t_vertex	*tail;

	if (!rooms)
		return (NULL);
	tail = *rooms;
	while (tail->next)
		tail = tail->next;
	return tail;
}
