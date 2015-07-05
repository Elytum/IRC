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
NAME = get_lines
#--------------Sources----------------------#
SOURCES =	ft_arrows.c				\
			ft_arrows2.c			\
			ft_dynamic.c			\
			ft_charmanage.c			\
			ft_clean.c				\
			ft_cursor.c				\
			ft_delete.c				\
			ft_inputs.c				\
			ft_lstrmanage.c			\
			ft_managechar.c			\
			ft_moves.c				\
			ft_put.c				\
			ft_special.c			\
			ft_termcaps.c

SRC = $(addprefix srcs/, $(SOURCES))

OBJ = $(SRC:.c=.o)

LIBNAME = get_lines.a

FLAGS = -Wall -Werror -Wextra

INC = -I./includes -I../libft

#--------------Sources----------------------#

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(LIBNAME) $(OBJ)
	@ranlib $(LIBNAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c  $(INC) $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(LIBNAME)

re: fclean all
