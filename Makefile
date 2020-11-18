# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 16:30:25 by lseema            #+#    #+#              #
#    Updated: 2020/11/18 21:15:04 by lseema           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEMIN = lem-in
CC = gcc -g -Wall -Wextra -Werror
SRC_DIR = srcs/
LIBFT_DIR = libft/
OBJ_DIR = obj/
LEMIN_SRCS = lem-in.c\
	validate.c
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
