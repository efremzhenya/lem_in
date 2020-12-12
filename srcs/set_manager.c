/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:29:10 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/12 19:29:10 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_set		*new_set_elem(t_vertex *room)
{
	t_set	*set;

	if (!(set = (t_set *)malloc(sizeof(t_set))))
		return (NULL);
	set->room = room;
	set->next = NULL;
	set->prev = NULL;
	return (set);
}

int			add_to_set(t_set **set, t_set *elem)
{
	t_set	*tail;

	if (!set || !elem)
		return (0);
	tail = *set;
	while (tail->next)
		tail = tail->next;
	tail->next = elem;
	elem->next = NULL;
	elem->prev = tail;
	return (1);
}

int			is_contain_in_set(t_set **set, size_t index)
{
	t_set	*tail;

	if (!*set)
		return (0);
	tail = *set;
	while (tail->next)
	{
		if (tail->room->index == index)
			return (1);
		tail = tail->next;
	}
	return (tail->room->index == index);
}

void		remove_in_set(t_set **set, t_set *elem)
{
	if (!*set || !elem)
		return ;
	if (*set == elem)
		*set = elem->next;
	if (elem->next != NULL)
		elem->next->prev = elem->prev;
	if (elem->prev != NULL)
		elem->prev->next = elem->next;
	free(elem);
}

t_set		*find_min_in_set(t_set **set)
{
	t_set	*min;
	t_set	*tail;

	if (!*set)
		return (NULL);
	min = *set;
	tail = *set;
	while (tail->next)
	{
		if (tail->room->distance < min->room->distance)
			min = tail;
		tail = tail->next;
	}
	return (tail->room->distance < min->room->distance ? tail : min);
}
