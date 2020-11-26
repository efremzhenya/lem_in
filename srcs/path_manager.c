/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 23:07:24 by lseema            #+#    #+#             */
/*   Updated: 2020/11/26 22:36:03 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem-in.h"

t_path	*new_path(size_t length, size_t *indexes)
{
	t_path *new_path;

	if (!(new_path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	new_path->vrt_indexes = indexes;
	new_path->length = length;
	new_path->next = NULL;
	return (new_path);
}

int		add_path(t_path **paths, t_path *path)
{
	t_path	*tail;

	if (!paths || !path)
		return (0);
	tail = *paths;
	while (tail->next)
		tail = tail->next;
	tail->next = path;
	return (1);
}
