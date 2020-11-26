/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 22:59:10 by lseema            #+#    #+#             */
/*   Updated: 2020/11/25 21:24:53 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

size_t		parse_lines(t_line **lines, t_lemin **lemin, t_vertex **rooms)
{
	char	*line;
	size_t	count;

	count = 0;
	while ((line = read_next_line()) != NULL)
	{
		if (parse_line(line, lemin, rooms))
			if (!*lines)
				*lines = new_line(&line);
			else
				add_line(lines, new_line(&line));
		else
		{
			free(line);
			return (0);
		}
		count++;
	}
	return count;
}

int		parse_line(char *line, t_lemin **lemin, t_vertex **rooms)
{
	size_t i;

	i = 0;
	if ((*lemin)->step == ANT)
		return parse_ants(line, lemin);
	else if ((*lemin)->step == ROOMS)
		if (!parse_room_type(line, lemin, rooms))
			(*lemin)->step = LINKS;
	if ((*lemin)->step == LINKS)
	{
		if (!(*lemin)->start_room || !(*lemin)->end_room)
			return (0);
		if (!((*lemin)->adj))
		{
			if (!((*lemin)->adj = (t_adj **)malloc(sizeof(t_adj *)
				* (*lemin)->rooms)))
				return (0);
			while (i < (*lemin)->rooms)
			{
				(*lemin)->adj[i] = new_adj(i);
				i++;
			}
		}
		return parse_link(line, lemin, rooms);
	}
	return (1);
}

char	*read_next_line()
{
	char	*line;
	int		res;

	line = NULL;
	while ((res = get_next_line(0, &line)) > 0)
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			return line;
		else if (*line && (*line == '#'))
		{
			free(line);
			continue;
		}
		else
			return line;
	}
	return NULL;
}
