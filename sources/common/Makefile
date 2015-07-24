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
NAME = common
#--------------Sources----------------------#
SOURCES =	commands.c			\
			chained_string.c

SRC = $(addprefix srcs/, $(SOURCES))

OBJ = $(SRC:.c=.o)

LIBNAME = common.a

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
