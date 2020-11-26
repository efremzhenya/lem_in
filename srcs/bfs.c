/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:40:54 by lseema            #+#    #+#             */
/*   Updated: 2020/11/26 23:54:38 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int		first_find_path(t_lemin **lemin)
{
	t_bfs *bfs;

	if (!new_queue(&(*lemin)->bfs_queue) || !init_bfs(lemin, &bfs))
		return (0);
	bfs_algorithm(lemin, &bfs);
	free_bfs(&bfs);
	clear_queue(&(*lemin)->bfs_queue);
	return (1);
}

void	free_bfs(t_bfs **bfs)
{
	if ((*bfs))
	{
		if ((*bfs)->distance)
			free((*bfs)->distance);
		if ((*bfs)->parent)
			free((*bfs)->parent);
		if ((*bfs)->used)
			free((*bfs)->used);
		free(*bfs);
	}
}

int		bfs_algorithm(t_lemin **lemin, t_bfs **bfs)
{
	t_adj				*curr_list;
	t_ilist				*tail;

	while ((*lemin)->bfs_queue->front)
	{
		curr_list = dequeue(&(*lemin)->bfs_queue);
		tail = curr_list->links;
		while (tail)
		{
			if (!(*bfs)->used[tail->index])
			{
				(*bfs)->used[tail->index] = 1;
				(*bfs)->parent[tail->index] = curr_list->index;
				(*bfs)->distance[tail->index] = (*bfs)->distance[curr_list->index] + 1;
				enqueue(&(*lemin)->bfs_queue, (*lemin)->adj[tail->index]);
				if (tail->index == (*lemin)->end_room->index)
				{
					clear_queue(&(*lemin)->bfs_queue);
					break;
				}
			}
			if (tail->next)
				tail = tail->next;
			else
				break;
		}
	}
	return reverse_finded_path(lemin, bfs);
}

int		init_bfs(t_lemin **lemin, t_bfs **bfs)
{
	size_t	i;

	i = 0;
	*bfs = (t_bfs*)malloc(sizeof(t_bfs));
	(*bfs)->used = (unsigned int *)malloc((*lemin)->rooms * sizeof(unsigned int));
	if (!(*bfs)->used)
		return (0);
	(*bfs)->parent = (size_t *)malloc((*lemin)->rooms * sizeof(size_t));
	if (!(*bfs)->parent)
		return (0);
	(*bfs)->distance = (size_t *)malloc((*lemin)->rooms * sizeof(size_t));
	if (!(*bfs)->distance)
		return (0);
	while (i < (*lemin)->rooms)
	{
		(*bfs)->used[i] = 0;
		(*bfs)->distance[i++] = 0;
	}
	(*bfs)->distance[(*lemin)->start_room->index] = 0;
	(*bfs)->used[(*lemin)->start_room->index] = 1;
	(*bfs)->parent[(*lemin)->end_room->index] = SIZE_MAX;
	enqueue(&(*lemin)->bfs_queue, (*lemin)->adj[(*lemin)->start_room->index]);
	return (1);
}

int		reverse_finded_path(t_lemin **lemin, t_bfs **bfs)
{
	size_t	curr_i;
	size_t	count;
	size_t	*path;

	curr_i = (*lemin)->end_room->index;
	count = (*bfs)->distance[curr_i];
	if ((*bfs)->parent[curr_i] == SIZE_MAX)
		return (0);
	if (!(path = (size_t *)malloc(sizeof(size_t) * (count + 1))))
		return (0);
	path[count--] = curr_i;
	while (count >= 0)
	{
		curr_i = (*bfs)->parent[curr_i];
		path[count] = curr_i;
		if (count == 0)
			break;
		count--;
	}
	if (!(*lemin)->paths)
		(*lemin)->paths = new_path((*bfs)->distance[(*lemin)->end_room->index], path);
	else
		add_path(&(*lemin)->paths, new_path((*bfs)->distance[(*lemin)->end_room->index], path));
	return (1);
}
