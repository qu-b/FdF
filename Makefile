# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:11:03 by fcullen           #+#    #+#              #
#    Updated: 2023/02/03 16:45:28 by fcullen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
FSANITIZE	= -fsanitize=address
OPENGL		= -framework OpenGL -framework AppKit

SRC			= main.c read_file.c draw.c utils.c events.c draw_utils.c init.c \
				transformations.c projections.c matrix_algebra.c controls.c \
				color.c
# draw_old.c 
OBJ			= $(SRC:.c=.o)

# Libs
LIBFT_DIR	= lib/libft/
LIBFT		= $(LIBFT_DIR)libft.a
MILIBX_DIR	= lib/minilibx_2019
MINILIBX	= libmlx.a

#Colors
GR = \033[32;1m
RC = \033[0m

all:		makelibs
			@$(MAKE) $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MINILIBX) $(OPENGL) -o $(NAME)
			@printf "\n -------------------------------- "
			@printf "\n$(GR)    ✅✅✅ FDF Compiled! ✅✅✅$(RC)" 
			@printf "\n -------------------------------- \n\n"

makelibs:
			@$(MAKE) -C $(LIBFT_DIR)
#			@$(MAKE) -C $(MILIBX_DIR)

san:		makelibs
			@$(MAKE) $(OBJ)
			@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(LIBFT) $(MINILIBX) $(OPENGL) -o $(NAME)

clean:
			$(MAKE) clean -C $(LIBFT_DIR)
			$(MAKE) clean -C $(MILIBX_DIR)
			$(RM) $(OBJ)

fclean:		clean
			@$(MAKE) fclean -C $(LIBFT_DIR)
			@$(RM) $(NAME)
			@echo Clean!

re:			fclean $(NAME)

.PHONY:		all clean fclean re


