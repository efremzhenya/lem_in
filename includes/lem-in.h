/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:41:38 by lseema            #+#    #+#             */
/*   Updated: 2020/11/18 21:05:43 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"

typedef struct		s_lem_in
{
	size_t					vrtx_count;
	size_t					edge_count;
	int						ants_count;
	t_vertex				start;
	t_vertex				end;
}							t_lem_in;

typedef struct		s_vertex
{
	char					*name;
	int						x;
	int						y;
	size_t					index;
}							t_vertex;

typedef struct		s_edge
{
	t_vertex				vrtx_start;
	t_vertex				vrtx_end;
}							t_edge;



#endif
