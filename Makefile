# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 16:30:25 by lseema            #+#    #+#              #
#    Updated: 2020/11/22 20:00:31 by lseema           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEMIN = lem-in
CC = gcc -g -Wall -Wextra -Werror
SRC_DIR = srcs/
LIBFT_DIR = libft/
OBJ_DIR = obj/
LEMIN_SRCS = lem-in.c\
	parse_lines.c\
	parse_ants.c\
	parse_room.c\
	vertex_manager.c\
	ilist_manager.c\
	line_manager.c\
	print_result.c\
	parse_links.c\
	validators.c\
	queue_manager.c\
	bfs.c\
	free.c

LEMIN_OBJ = ${LEMIN_SRCS:c=o}

all: $(LEMIN)

$(addprefix $(OBJ_DIR), %.o): $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -I libft/ -I includes/ -c -o $@ $^

$(LEMIN): $(addprefix $(OBJ_DIR), $(LEMIN_OBJ))
	@make -C libft/
	@$(CC) $(addprefix $(OBJ_DIR), $(LEMIN_OBJ)) $(LIBFT_DIR)libft.a -I libft/ -o $(LEMIN)
	@echo "lem-in compiled"

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(LEMIN)

re: fclean all
