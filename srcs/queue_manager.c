/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:44:17 by lseema            #+#    #+#             */
/*   Updated: 2020/11/23 23:20:41 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int		new_queue(t_queue **queue)
{
	if (!(*queue = (t_queue*)malloc(sizeof(t_queue))))
		return (0);
	(*queue)->front = NULL;
	(*queue)->rear = NULL;
	return (1);
}

void	enqueue(t_queue **queue, t_adj *adj)
{
	if (!(*queue)->rear)
	{
		(*queue)->front = adj;
		(*queue)->rear = adj;
	}
	else
	{
		(*queue)->rear->next = adj;
		(*queue)->rear = adj;
	}
}

t_adj	*dequeue(t_queue **queue)
{
	t_adj		*elem;

	if (!(*queue)->front)
		elem = NULL;
	else if ((*queue)->front == (*queue)->rear)
	{
		elem = (*queue)->front;
		(*queue)->front = NULL;
		(*queue)->rear = NULL;
	}
	else
	{
		elem = (*queue)->front;
		(*queue)->front = (*queue)->front->next;
		elem->next = NULL;
	}
	return elem;
}

void	clear_queue(t_queue **queue)
{
	while ((*queue)->front)
		dequeue(queue);
}
