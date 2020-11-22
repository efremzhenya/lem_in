/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:42:01 by lseema            #+#    #+#             */
/*   Updated: 2020/11/21 23:16:59 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

t_line	*new_line(char **value)
{
	t_line *line;

	if (!(line = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	line->value = *value;
	line->next = NULL;
	line->prev = NULL;
	return (line);
}

int		add_line(t_line **lines, t_line *line)
{
	t_line	*tail;

	if (!lines || !line)
		return (0);
	tail = *lines;
	while (tail->next)
		tail = tail->next;
	tail->next = line;
	line->next = NULL;
	line->prev = tail;
	return (1);
}
