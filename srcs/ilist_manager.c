/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ilist_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:27:46 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/12 19:27:46 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ilist			*new_ilist(size_t index, int weight, int is_blocked)
{
	t_ilist		*elem;

	if (!(elem = (t_ilist *)malloc(sizeof(t_ilist))))
		return (NULL);
	elem->index = index;
	elem->weight = weight;
	elem->is_blocked = is_blocked;
	elem->next = NULL;
	return (elem);
}

int				add_ilist(t_ilist **list, t_ilist *elem)
{
	t_ilist		*tail;

	if (!list || !elem)
		return (0);
	tail = *list;
	while (tail->next)
		tail = tail->next;
	tail->next = elem;
	return (1);
}

t_adj			*new_adj(t_vertex *room, size_t index)
{
	t_adj		*adj;

	if (!(adj = (t_adj *)malloc(sizeof(t_adj))))
		return (NULL);
	adj->index = index;
	adj->room = room;
	adj->links = NULL;
	return (adj);
}

int				init_adj(t_vertex **vertexes, t_lemin **lemin)
{
	t_vertex	*rooms;
	size_t		i;

	if (!*vertexes)
		return (0);
	if (!((*lemin)->adj = (t_adj **)malloc(sizeof(t_adj *) * (*lemin)->rooms)))
		return (0);
	i = 0;
	rooms = *vertexes;
	while (rooms->next)
	{
		(*lemin)->adj[i] = new_adj(rooms, i);
		i++;
		rooms = rooms->next;
	}
	(*lemin)->adj[i] = new_adj(rooms, i);
	return (1);
}

int				is_link_exists(size_t ind1, size_t ind2,
								t_adj **row, size_t num)
{
	size_t		i;
	t_ilist		*tail;

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
			break ;
		}
		else
			i++;
	}
	return (0);
}
