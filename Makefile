# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:11:03 by marvin            #+#    #+#              #
#    Updated: 2023/02/06 19:23:22 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
FSANITIZE	= -fsanitize=address
OPENGL		= -framework OpenGL -framework AppKit

SRC			= main.c read_file.c read_file_2.c draw.c events.c draw_utils.c init.c \
				proj_1.c proj_2.c proj_3.c matrix_algebra.c controls.c \
				color.c controls2.c utils.c utils_2.c

OBJ			= $(SRC:.c=.o)
OBJ_DIR		= obj/

# Libs
LIBFT_DIR	= lib/libft/
LIBFT		= $(LIBFT_DIR)libft.a
MILIBX_DIR	= lib/minilibx_2019
MINILIBX	= libmlx.a

#Colors
GR = \033[32;1m
RC = \033[0m

define HEADER
    _______ __       __        ______         
   / ____(_) /  ____/ /__     / ____/__  _____
  / /_  / / /  / __  / _ \   / /_  / _ \/ ___/
 / __/ / / /  / /_/ /  __/  / __/ /  __/ /    
/_/   /_/_/___\__,_/\___/__///    \___/_/     
         / __/______  __/ / /__  ____         
        / /_/ ___/ / / / / / _ \/ __ \        
       / __/ /__/ /_/ / / /  __/ / / /        
      /_/  \___/\__,_/_/_/\___/_/ /_/         
                                              
endef
export HEADER

all:		makelibs
			@$(MAKE) $(NAME)

$(NAME):	$(OBJ) | $(OBJF)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MINILIBX) $(OPENGL) -o $(NAME)
			@printf "\n -------------------------------- "
			@printf "\n$(GR)       FDF Compiled! ✅$(RC)" 
			@printf "\n -------------------------------- \n\n"
			@echo "$$HEADER"

$(OBJF):
			mkdir -p $(OBJ_DIR)
makelibs:
			@$(MAKE) -C $(LIBFT_DIR)

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


