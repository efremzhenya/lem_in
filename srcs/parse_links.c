/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:28:30 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/19 13:46:06 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			no_links_exist(size_t index1, size_t index2, t_lemin ***lemin)
{
	if (!is_link_exists(index1, index2, (*(*lemin))->adj, (*(*lemin))->rooms))
	{
		if (((*(*lemin))->adj[index1]->links) == NULL)
			(*(*lemin))->adj[index1]->links = new_ilist(index2, 1, 0);
		else
			add_ilist(&(*(*lemin))->adj[index1]->links,
					new_ilist(index2, 1, 0));
		if (((*(*lemin))->adj[index2]->links) == NULL)
			(*(*lemin))->adj[index2]->links = new_ilist(index1, 1, 0);
		else
			add_ilist(&(*(*lemin))->adj[index2]->links,
					new_ilist(index1, 1, 0));
		(*(*lemin))->links++;
		return (1);
	}
	return (0);
}

int			parse_link(char *line, t_lemin **lemin, t_vertex **rooms)
{
	char	**splits;
	size_t	index1;
	size_t	index2;

	if (!*line || *line == '#' || ft_chrcount(line, '-') != 1)
		return (0);
	splits = ft_strsplit(line, '-');
	if (splits[0] && splits[1] && ft_strlen(splits[0]) > 0 &&
		ft_strlen(splits[1]) > 0 && ft_strcmp(splits[0], splits[1]) &&
		is_room_contain(rooms, splits[0]) && is_room_contain(rooms, splits[1]))
	{
		index1 = get_room_index(splits[0], rooms);
		index2 = get_room_index(splits[1], rooms);
		if (no_links_exist(index1, index2, &lemin))
		{
			free_str_arr(splits);
			return (1);
		}
	}
	return (free_str_arr(splits));
}

t_ilist		*find_link_by_index(t_ilist **ilist, size_t index)
{
	t_ilist	*tail;

	if (!*ilist)
		return (NULL);
	tail = *ilist;
	while (tail->next)
	{
		if (tail->index == index)
			return (tail);
		tail = tail->next;
	}
	return (tail->index == index ? tail : NULL);
}

void		free_links(t_ilist **links)
{
	t_ilist	*tail;

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
