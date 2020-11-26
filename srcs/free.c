/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:43:33 by lseema            #+#    #+#             */
/*   Updated: 2020/11/27 00:01:13 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void	free_all(t_lemin **lemin, t_line **lines, t_vertex **rooms)
{
	if (lemin)
	{
		if ((*lemin)->rooms > 0 && (*lemin)->adj)
			free_adj((*lemin)->adj, (*lemin)->rooms);
		if ((*lemin)->bfs_queue)
			free((*lemin)->bfs_queue);
		if ((*lemin)->paths)
			free_paths(&(*lemin)->paths);
		free(*lemin);
	}
	if (*lines)
		free_lines(lines);
	if (*rooms)
		free_rooms(rooms);
}

void	free_adj(t_adj **row, size_t count)
{
	size_t i;

	i = 0;
	while (i < count)
	{
		free_links(&row[i]->links);
		free(row[i]);
		i++;
	}
	free(row);
}

void	free_links(t_ilist **links)
{
	t_ilist *tail;

	if (*links)
	{
		tail = *links;
		while (tail->next)
		{
			*links = tail;
			tail = tail->next;
			free(*links);
		}
		free(tail);
	}
}

void	free_lines(t_line **lines)
{
	t_line *tail;

	if (*lines)
	{
		tail = *lines;
		while (tail->next)
		{
			*lines = tail;
			tail = tail->next;
			free((*lines)->value);
			free(*lines);
		}
		free(tail->value);
		free(tail);
	}
}

void	free_rooms(t_vertex **rooms)
{
	t_vertex *tail;

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

int		free_str_arr(char **temp)
{
	size_t i;

	i = 0;
	while (temp[i])
		free(temp[i++]);
	free(temp);
	return (0);
}

void	free_paths(t_path **paths)
{
	t_path *tail;

	if (*paths)
	{
		tail = *paths;
		while (tail->next)
		{
			*paths = tail;
			tail = tail->next;
			free((*paths)->vrt_indexes);
			free(*paths);
		}
		free(tail->vrt_indexes);
		free(tail);
	}
}
