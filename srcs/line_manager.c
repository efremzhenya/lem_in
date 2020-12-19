/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpasty <jpasty@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:28:01 by jpasty            #+#    #+#             */
/*   Updated: 2020/12/12 19:28:01 by jpasty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_line		*new_line(char **value)
{
	t_line	*line;

	if (!(line = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	line->value = *value;
	line->next = NULL;
	return (line);
}

int			add_line(t_line **lines, t_line *line)
{
	t_line	*tail;

	if (!lines || !line)
		return (0);
	tail = *lines;
	while (tail->next)
		tail = tail->next;
	tail->next = line;
	line->next = NULL;
	return (1);
}
