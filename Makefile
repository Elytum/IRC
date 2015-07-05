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

.PHONY: $(NAME) build clean fclean re

all: build cpy

build:
	@echo "$(OK_COLOR)Building client$(NO_COLOR)"
	make -C sources/client
	@echo "$(OK_COLOR)Building server$(NO_COLOR)"
	make -C sources/server
	@echo "$(OK_COLOR)Building done$(NO_COLOR)"

cpy:
	@echo "$(OK_COLOR)Copying binaries$(NO_COLOR)"
	@cp sources/client/client .
	@cp sources/server/server .

clean:
	@echo "$(OK_COLOR)Clearing client$(NO_COLOR)"
	make clean -C sources/client
	@echo "$(OK_COLOR)Clearing server$(NO_COLOR)"
	make clean -C sources/server
	@echo "$(OK_COLOR)Clearing done$(NO_COLOR)"
	
fclean:
	@echo "$(OK_COLOR)Force clean client$(NO_COLOR)"
	make fclean -C sources/client
	@echo "$(OK_COLOR)Force clean server$(NO_COLOR)"
	make fclean -C sources/server
	@echo "$(OK_COLOR)Force clean done$(NO_COLOR)"

re: fclean build