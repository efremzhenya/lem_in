/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:41:38 by lseema            #+#    #+#             */
/*   Updated: 2020/11/19 00:12:23 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"

typedef struct		s_vertex
{
	char					*name;
	int						x;
	int						y;
	size_t					index;
}							t_vertex;

typedef struct		s_lemin
{
	size_t					vrtx_count;
	size_t					edge_count;
	int						ants_count;
	t_vertex				*start_room;
	t_vertex				*end_room;
}							t_lemin;

typedef struct		s_edge
{
	t_vertex				*start_vrtx;
	t_vertex				*end_vrtx;
}							t_edge;

int							validate();
int							parse(t_lemin **lemin);
int							parse_ants(t_lemin **lemin, char *line);
int							validate_positive_num(char *argv);
char						*read_next_line();
void						free_all(t_lemin **lemin);

#endif
