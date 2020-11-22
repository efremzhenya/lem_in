/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilist_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 06:01:54 by lseema            #+#    #+#             */
/*   Updated: 2020/11/22 20:09:58 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

t_ilist		*new_ilist_elem(size_t index)
{
	t_ilist *elem;

	if (!(elem = (t_ilist *)malloc(sizeof(t_ilist))))
		return (NULL);
	elem->index = index;
	elem->next = NULL;
	return (elem);
}

int			add_ilist(t_ilist **list, t_ilist *elem)
{
	t_ilist	*tail;
	if (!list || !elem)
		return (0);
	tail = *list;
	while (tail->next)
		tail = tail->next;
	tail->next = elem;
	return (1);
}

t_adj	*new_adj(size_t index)
{
	t_adj *adj;
	if (!(adj = (t_adj *)malloc(sizeof(t_adj))))
		return (NULL);
	adj->index = index;
	adj->links = NULL;
	adj->next = NULL;
	return (adj);
}

int			is_link_exists(size_t ind1, size_t ind2, t_adj **row, size_t num)
{
	size_t 	i;
	t_ilist	*tail;

	i = 0;
	while (i < num)
	{
		if (row[i]->index == ind1 || row[i]->index == ind2)
		{
			if (!row[i]->links)
				return (0);
			tail = row[i]->links;
			while (tail->next)
			{
				if (tail->index == ((row[i]->index == ind1) ? ind2 : ind1))
					return (1);
				tail = tail->next;
			}
			if (tail->index == ((row[i]->index == ind1) ? ind2 : ind1))
				return (1);
			break;
		}
		else
			i++;
	}
	return (0);
}
