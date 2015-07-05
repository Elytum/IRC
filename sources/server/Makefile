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

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

# -------------Compilateur------------------#
CC		=	gcc
#--------------Name-------------------------#
NAME	=	server
MYPATH	=	$(HOME)
#--------------Sources----------------------#
FILES	=	main.c								\
			client_actions.c					\
			connection.c						\
			message_adding.c					\
			messages.c							\
			pool.c								\
			pseudo.c							\
			read.c

INC		=	-I./includes/ -I../common/includes/ -I../inputs/includes/ -I../libft/
CCFLAGS	=	-Wall -Wextra -Werror -g

SRCS	=	$(addprefix srcs/, $(FILES))
OBJS	=	$(SRCS:.c=.o)

#--------------Actions----------------------#

.PHONY: MLX $(NAME) clean fclean re

all: $(NAME)

$(NAME): LIBFT INPUTS COMMON $(OBJS)
	$(CC) $(CCFLAGS) $(INC) $(OBJS) -o $(NAME) ../libft/libft.a ../inputs/get_lines.a ../common/common.a -lncurses

LIBFT:
	@echo "$(OK_COLOR)Building libft$(NO_COLOR)"
	@make -C ../libft

INPUTS:
	@echo "$(OK_COLOR)Building inputs$(NO_COLOR)"
	@make -C ../inputs

COMMON:
	@echo "$(OK_COLOR)Building common$(NO_COLOR)"
	@make -C ../common

%.o: %.c
	$(CC) $(CCFLAGS) -c $(INC) $< -o $@
	
clean:
	@echo "$(OK_COLOR)Clearing libft$(NO_COLOR)"
	make clean -C ../libft
	@echo "$(OK_COLOR)Clearing inputs$(NO_COLOR)"
	make clean -C ../inputs
	@echo "$(OK_COLOR)Clearing common$(NO_COLOR)"
	make clean -C ../common
	rm -f $(OBJS)
	
fclean:
	@echo "$(OK_COLOR)Force clean libft$(NO_COLOR)"
	make fclean -C ../libft
	@echo "$(OK_COLOR)Force clean inputs$(NO_COLOR)"
	make fclean -C ../inputs
	@echo "$(OK_COLOR)Force clean common$(NO_COLOR)"
	make fclean -C ../common
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all
