/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:41:38 by lseema            #+#    #+#             */
/*   Updated: 2020/11/22 20:01:49 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"

typedef struct		s_ilist
{
	size_t					index;
	struct s_ilist			*next;
}							t_ilist;

typedef struct		s_adj
{
	size_t					index;
	struct s_adj			*next;		//используется толко в очереди
	t_ilist					*links;
}							t_adj;

typedef struct		s_queue
{
	t_adj			*front;
	t_adj			*rear;
}					t_queue;

typedef struct		s_vertex
{
	char					*name;
	int						x;
	int						y;
	size_t					index;
	struct s_vertex			*next;
	struct s_vertex			*prev;
}							t_vertex;

typedef struct		s_lemin
{
	size_t					rooms;
	size_t					links;
	int						ants;
	size_t					lines;
	struct s_vertex			*start_room;
	struct s_vertex			*end_room;
	struct s_adj			**adj;
	int						step;
	int						next_is_start;
	int						next_is_end;
	t_queue					*bfs_queue;
}							t_lemin;

typedef struct		s_line
{
	char					*value;
	struct s_line			*prev;
	struct s_line			*next;
}							t_line;

//main
int							init_lemin(t_lemin **lemin);
void						print_lines(t_line **lines);

//line
t_line						*new_line(char **value);
int							add_line(t_line **lines, t_line *line);
size_t						parse_lines(t_line **lines, t_lemin **lemin, t_vertex **rooms);
int							parse_line(char *line, t_lemin **lemin, t_vertex **rooms);
char						*read_next_line();

//ants
int							parse_ants(char *line, t_lemin **lemin);
int							valid_positive_int(char *argv);

//rooms
int							add_vertex(t_vertex **rooms, t_vertex *vertex);
t_vertex					*new_vertex(char *name, size_t index, int x, int y);
int							is_room_dup(t_vertex **rooms, char *name, int x, int y);
int							is_room_contain(t_vertex	**rooms, char *name);

size_t						get_room_index(char *name, t_vertex **rooms);
//parse_room_type
int							parse_room_type(char *line, t_lemin **lemin, t_vertex **rooms);
int							parse_room(char *line, t_lemin **lemin, t_vertex **rooms);
size_t						ft_chrcount(char *line, char c);
int							valid_int(char *argv);

//list
t_ilist						*new_ilist_elem(size_t index);
int							add_ilist(t_ilist **list, t_ilist *elem);
int							is_link_exists(size_t ind1, size_t ind2, t_adj **row, size_t num);

//adjacency
t_adj						*new_adj(size_t index);
int							parse_link(char *line, t_lemin **lemin, t_vertex **rooms);

//free
void						free_all(t_lemin **lemin, t_line **lines, t_vertex **rooms);
void						free_lines(t_line **lines);
void						free_rooms(t_vertex **rooms);
void						free_links(t_ilist **list);
int							free_str_arr(char **temp);
void						free_adj(t_adj **row, size_t count);

//queue
int							new_queue(t_queue **queue);
void						enqueue(t_queue **queue, t_adj *adj);
t_adj						*dequeue(t_queue **queue);


//bfs
void						bfs(t_lemin **lemin);

#endif
