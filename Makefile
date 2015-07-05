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

#--------------Name-------------------------#

#--------------Sources----------------------#

#--------------Actions----------------------#

.PHONY: $(NAME) clean fclean re

all: $(NAME)

$(NAME):
	make client
	make server

clean:
	make clean -C client
	make clean -C server
	
fclean:	
	make fclean -C client
	make fclean -C server

re:
	make re -C client
	make re -C server
