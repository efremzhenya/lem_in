/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:40:54 by lseema            #+#    #+#             */
/*   Updated: 2020/11/22 20:43:15 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

void	bfs(t_lemin **lemin)
{
	unsigned short int	used[(*lemin)->rooms];
	size_t				i;
	t_adj				*curr_list;
	t_ilist				*tail;

	while (i < (*lemin)->rooms)
		used[i++] = 0;
	used[(*lemin)->start_room->index] = 1;
	enqueue(&(*lemin)->bfs_queue, (*lemin)->adj[(*lemin)->start_room->index]);
	while ((*lemin)->bfs_queue->rear)
	{
		curr_list = dequeue((*lemin)->bfs_queue);
		tail = curr_list->links;
		while (tail && tail->next)
		{
			if (!used[tail->index])
			{
				//дошел сюда
			}
			tail = tail->next;
		}

	}

}
