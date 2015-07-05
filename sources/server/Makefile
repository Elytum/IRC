# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achazal <achazal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:54:29 by achazal           #+#    #+#              #
#    Updated: 2014/12/13 12:55:35 by achazal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------Compilateur------------------#
CC		=	gcc
#--------------Name-------------------------#
NAME	=	fdf
MYPATH	=	$(HOME)
#--------------Sources----------------------#
FILES	=	main.c								\
			parsing/get_next_line.c				\
			parsing/get_map.c					\
			maths/matrices.c					\
			maths/matrices_moves.c				\
			maths/matrices_utils.c				\
			maths/vectors.c						\
			render/draw_map.c					\
			render/draw_line.c					\
			lib/init.c							\
			lib/hooks.c							\
			lib/extra_hooks.c					\
			lib/moves.c							\
			lib/libft.c							\
			lib/libft2.c						\
			lib/libft3.c						\
			lib/mlx_tools.c

INC		=	-I minilibx_macos -I./libft/ -I./includes
CCFLAGS	=	-Wall -Wextra -Werror -g
LDFLAGS	=	-framework glut -framework Cocoa -framework OpenGL

SRCS	=	$(addprefix srcs/, $(FILES))
OBJS	=	$(SRCS:.c=.o)

#--------------Actions----------------------#

.PHONY: MLX $(NAME) clean fclean re

all: $(NAME)

MLX:
	make -C minilibx_macos

$(NAME): MLX $(OBJS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $(INC) $(OBJS) -o $(NAME) minilibx_macos/libmlx.a -O3

%.o: %.c
	$(CC) $(CCFLAGS) -c  $(INC) $< -o $@
	
clean:
	make clean -C minilibx_macos
	rm -f $(OBJS)
	
fclean:	clean
	make clean -C minilibx_macos
	rm -f $(NAME)

re: fclean all
	make re -C minilibx_macos
