# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:11:03 by fcullen           #+#    #+#              #
#    Updated: 2023/01/23 11:47:53 by fcullen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
FSANITIZE	= -fsanitize=address
OPENGL		= -framework OpenGL -framework AppKit

SRC			= main.c read_file.c draw.c utils.c events.c
OBJ			= $(SRC:.c=.o)

# Libs
LIBFT_DIR	= lib/libft/
LIBFT		= $(LIBFT_DIR)libft.a
MILIBX_DIR	= lib/minilibx_2019
MINILIBX	= libmlx.a



all:		makelibs
			@$(MAKE) $(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MINILIBX) $(OPENGL) -o $(NAME)

makelibs:
			@$(MAKE) -C $(LIBFT_DIR)
#			@$(MAKE) -C $(MILIBX_DIR)

san:		makelibs
			@$(MAKE) $(OBJ)
			@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(LIBFT) $(MINILIBX) $(OPENGL) -o $(NAME)

clean:
			@$(MAKE) clean -C $(LIBFT_DIR)
			@$(MAKE) clean -C $(MILIBX_DIR)
			$(RM) $(OBJ)

fclean:		clean
			@$(MAKE) fclean -C $(LIBFT_DIR)
			$(RM) $(NAME)
			@echo Clean!

re:			fclean $(NAME)

.PHONY:		all clean fclean re