/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:28:21 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/12 19:28:21 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t		parse_lines(t_line **lines, t_lemin **lemin, t_vertex **rooms)
{
	char	*line;
	size_t	count;

	count = 0;
	freopen("map.txt", "r", stdin);
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
	return (count);
}

int			parse_line(char *line, t_lemin **lemin, t_vertex **rooms)
{
	if ((*lemin)->step == ANT)
		return (parse_ants(line, lemin));
	else if ((*lemin)->step == ROOMS)
		if (!parse_room_type(line, lemin, rooms))
			(*lemin)->step = LINKS;
	if ((*lemin)->step == LINKS)
	{
		if (!(*lemin)->start_room || !(*lemin)->end_room)
			return (0);
		if (!((*lemin)->adj))
			init_adj(rooms, lemin);
		return (parse_link(line, lemin, rooms));
	}
	return (1);
}

char		*read_next_line(void)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (*line && (*line == '#') && ft_strcmp(line, "##start") != 0 &&
				ft_strcmp(line, "##end") != 0)
			free(line);
		else
			return (line);
	}
	return (NULL);
}

void		free_lines(t_line **lines)
{
	t_line	*tail;

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
