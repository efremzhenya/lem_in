/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 06:01:23 by lseema            #+#    #+#             */
/*   Updated: 2020/12/01 20:57:39 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

int		parse_link(char *line, t_lemin **lemin, t_vertex **rooms)
{
	char	**splits;
	size_t	index1;
	size_t	index2;

	if (!*line || *line == '#' || ft_chrcount(line, '-') != 1)
		return (0);
	splits = ft_strsplit(line, '-');
	if (splits[0] && splits[1] && ft_strlen(splits[0]) > 0 && *splits[1] != '#'
		&& ft_strlen(splits[1]) > 0 && ft_strcmp(splits[0], splits[1])
		&& is_room_contain(rooms, splits[0]) && is_room_contain(rooms, splits[1]))
	{
		index1 = get_room_index(splits[0], rooms);
		index2 = get_room_index(splits[1], rooms);
		if (!is_link_exists(index1, index2, (*lemin)->adj, (*lemin)->rooms))
		{
			free_str_arr(splits);
			if (((*lemin)->adj[index1]->links) == NULL)
				(*lemin)->adj[index1]->links = new_ilist_elem(index2, 1, 0);
			else
				add_ilist(&(*lemin)->adj[index1]->links, new_ilist_elem(index2, 1, 0));
			if (((*lemin)->adj[index2]->links) == NULL)
				(*lemin)->adj[index2]->links = new_ilist_elem(index1, 1, 0);
			else
				add_ilist(&(*lemin)->adj[index2]->links, new_ilist_elem(index1, 1, 0));
			(*lemin)->links++;
			return (1);
		}
	}
	return free_str_arr(splits);
}
