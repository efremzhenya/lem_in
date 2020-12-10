/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:41:38 by lseema            #+#    #+#             */
/*   Updated: 2020/12/10 21:25:05 by jpasty           ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"

//BOOLEAN
# define TRUE 1
# define FALSE 0

//VERTEX TYPE
# define DUPLEX 0
# define IN 1
# define OUT 2

//CURRENT DATA READ STEP
# define ANT 0
# define ROOMS 1
# define LINKS 2

typedef struct				s_ant
{
	size_t					path_index;
	size_t					room_index;
	unsigned int			is_active:1;
}							t_ant;

typedef struct				s_path_room
{
	struct s_vertex			*room;
	struct s_path_room		*next;
}							t_path_room;

typedef struct				s_path
{
	size_t					length;
	t_path_room				*rooms;
	struct s_path			*next;
}							t_path;

typedef struct				s_ilist
{
	size_t					index;
	int						weight:2;
	unsigned int			is_blocked;
	struct s_ilist			*next;
}							t_ilist;

typedef struct				s_adj
{
	size_t					index;
	struct s_vertex			*room;
	t_ilist					*links;
}							t_adj;

typedef struct				s_queue
{
	t_adj					*front;
	t_adj					*rear;
}							t_queue;

typedef	struct 				s_set
{
	struct s_vertex			*room;
	struct s_set			*next;
	struct s_set			*prev;
}							t_set;

typedef struct				s_vertex
{
	char					*name;
	int						x;
	int						y;
	size_t					index;
	size_t					distance;
	size_t					parent_index;
	unsigned int			splited:1;
	struct s_vertex			*next;
	struct s_vertex			*prev;
}							t_vertex;

typedef struct				s_lemin
{
	size_t					rooms;
	size_t					links;
	int						ants;
	size_t					lines;
	unsigned int			routes;
	struct s_vertex			*start_room;
	struct s_vertex			*end_room;
	struct s_adj			**adj;
	struct s_set			*set;
	int						step;
	int						next_is_start;
	int						next_is_end;
	t_path					*paths;
	size_t					paths_count;
	size_t					result_steps_count;
}							t_lemin;

typedef struct				s_line
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
t_vertex					*get_last_added(t_vertex **rooms);
size_t						get_room_index(char *name, t_vertex **rooms);

//parse_room_type
int							parse_room_type(char *line, t_lemin **lemin, t_vertex **rooms);
int							parse_room(char *line, t_lemin **lemin, t_vertex **rooms);
size_t						ft_chrcount(char *line, char c);
int							valid_int(char *argv);

//list
t_ilist						*new_ilist(size_t index, int weight, int is_blocked);
int							add_ilist(t_ilist **list, t_ilist *elem);
int							is_link_exists(size_t ind1, size_t ind2, t_adj **row, size_t num);
t_ilist						*find_link_by_index(t_ilist **ilist, size_t index);

//adjacency
t_adj						*new_adj(t_vertex *room, size_t index);
int							init_adj(t_vertex **vertexes, t_lemin **lemin);
int							parse_link(char *line, t_lemin **lemin, t_vertex **rooms);

//free
void						free_all(t_lemin **lemin, t_line **lines, t_vertex **rooms);
void						free_lines(t_line **lines);
void						free_rooms(t_vertex **rooms);
void						free_links(t_ilist **list);
int							free_str_arr(char **temp);
void						free_adj(t_adj **row, size_t count);
void						free_path_rooms(t_path_room **path_rooms);

//path
t_path						*new_path();
int							add_path(t_path **paths, t_path *path);
t_path_room					*new_path_room(t_vertex *room);
int							add_path_room(t_path_room **path_rooms, t_path_room *path_room);
void						free_paths(t_path **paths);
int							push_path_room(t_path_room **path_rooms, t_path_room *path_room);
t_path						*reverse_finded_path(t_lemin **lemin);
size_t						result_steps_count(t_lemin **lemin, t_path **paths);
void						get_sorted_paths_lengths(size_t lens[], size_t path_count, t_path **paths, t_vertex **path_with_idexes);
void						calc_koefs(int koef[], size_t count, size_t lengths[]);
void						free_last_path(t_path **paths);

//set
t_set						*new_set_elem(t_vertex *room);
int							add_to_set(t_set **set, t_set *elem);
void						remove_in_set(t_set **set, t_set *elem);
int							is_contain_in_set(t_set **set, size_t index);
t_set						*find_min_in_set(t_set **set);
void						free_set(t_set **set);

//dejkstra
void						dejkstra_main(t_lemin **lemin, t_vertex **vertexes);
void						dejkstra_init(t_vertex **vertexes, t_lemin **lemin);

//suurballe
void						suurballe_main(t_lemin **lemin, t_vertex **rooms, size_t steps);
void						split_rooms_on_paths(t_lemin **lemin);
void						split_and_set_weight(t_path_room **path_rooms, t_lemin **lemin);
int							find_common_links(t_lemin **lemin, t_path *path, short int **matrix);
t_path						*create_new_path(t_lemin **lemin, t_path *path,
											short int **matrix, size_t index);
short int					combine_paths(t_lemin **lemin, t_path *path, short int **matrix);
short int					**init_adj_matrix(t_lemin **lemin);
void						free_adj_matrix(short int **matrix, size_t count);
void						init_rooms(t_lemin **lemin, t_vertex **rooms);
void						insert_sort_mod(size_t arr[], size_t n, t_vertex **paths, size_t i);

//ants
void						ants_go(t_lemin **lemin, t_vertex **paths, int ants, size_t i);
t_vertex					**indexing_paths(t_lemin **lemin, size_t i, size_t j);
void						ants_init(t_ant **ants, int count);
int							move_ants(t_lemin **lemin, t_ant **ants, t_vertex **paths, int i);
void						free_ants(t_lemin **lemin, t_ant **ants, t_vertex **paths);

#endif
