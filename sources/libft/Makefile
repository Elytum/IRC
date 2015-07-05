#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achazal <achazal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/28 22:41:37 by achazal           #+#    #+#              #
#    Updated: 2015/01/28 22:41:42 by achazal          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY: all, clean, fclean, mrproper, re, fast

CC = clang
NAME = libft.a
CFLAGS = -Wall -Werror -Wextra -pedantic -I./ -Xclang -fcolor-diagnostics -O3
SOURCE = ft_atoi.c \
        ft_bzero.c \
        ft_isalnum.c \
        ft_isalpha.c \
        ft_isascii.c \
        ft_isdigit.c \
        ft_islower.c \
        ft_isprint.c \
        ft_isspace.c \
        ft_isupper.c \
        ft_itoa.c \
        ft_memalloc.c \
        ft_memccpy.c \
        ft_memchr.c \
        ft_memcmp.c \
        ft_memcpy.c \
        ft_memdel.c \
        ft_memmove.c \
        ft_memset.c \
        ft_putchar.c \
        ft_putchar_fd.c \
        ft_putendl.c \
        ft_putendl_fd.c \
        ft_putnbr.c \
        ft_putnbr_fd.c \
        ft_putstr.c \
        ft_putstr_fd.c \
        ft_putstrarray.c \
        ft_strarraylen.c \
        ft_strcat.c \
        ft_strchr.c \
        ft_strclr.c \
        ft_strcmp.c \
        ft_strcpy.c \
        ft_strdel.c \
        ft_strdup.c \
        ft_strequ.c \
        ft_strisin.c \
        ft_striter.c \
        ft_striteri.c \
        ft_strjoin.c \
        ft_strlcat.c \
        ft_strlen.c \
        ft_strmap.c \
        ft_strmapi.c \
        ft_strmatch.c \
        ft_strncat.c \
        ft_strncmp.c \
        ft_strncpy.c \
        ft_strndup.c \
        ft_strnequ.c \
        ft_strnew.c \
        ft_strnstr.c \
        ft_strrchr.c \
        ft_strrev.c \
        ft_strstr.c \
        ft_strsub.c \
        ft_strtrim.c \
        ft_swap.c \
        ft_tolower.c \
        ft_toupper.c \
        ft_putstrarray_fd.c \
        ft_lstnew.c \
        ft_lstdelone.c \
        ft_lstdel.c \
        ft_lstadd.c \
        ft_lstiter.c \
        ft_lstmap.c \
		ft_strsplit.c \
		ft_lstpush.c \
		ft_putintarray.c \
		ft_isodd.c \
		ft_iseven.c \
		ft_isodd_digit.c \
		ft_iseven_digit.c \
		ft_isword.c

OBJ = $(SOURCE:.c=.o)


ifeq ($(FAST), 1)
	CFLAGS := -O3 $(CFLAGS)
else
	CFLAGS := -O2 $(CFLAGS)
endif


all : $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[31;1m• \033[0mCreating archive $@ ...\033[55G\c"
	@export result=`ar rcs $@ $(OBJ) 2>&1` ; \
	if [ "$$result" = "" ] ; then \
		echo "\033[37;1m[\033[32mOK !\033[37m]\033[0m" ; \
	else \
		echo "\033[37;1m[\033[31mFAIL\033[37m]\033[0m" ; \
		echo "\n$$result" ; \
		exit 1 ; \
	fi

ifeq ($(FAST), 1)

%.o : %_fast.c libft.h
	@echo "\033[31;1m• \033[0mCreating object file $@ ...\033[55G\c"
	@export result=`$(CC) $(CFLAGS) -c $< -o $@ 2>&1` ; \
	if [ "$$result" = "" ] ; then \
		echo "\033[37;1m[\033[32mOK !\033[37m]\033[0m" ; \
	else \
		echo "\033[37;1m[\033[31mFAIL\033[37m]\033[0m" ; \
		echo "\n$$result" ; \
		exit 1 ; \
	fi
endif


%.o : %.c libft.h
	@echo "\033[31;1m• \033[0mCreating object file $@ ...\033[55G\c"
	@export result=`$(CC) $(CFLAGS) -c $< -o $@ 2>&1` ; \
	if [ "$$result" = "" ] ; then \
		echo "\033[37;1m[\033[32mOK !\033[37m]\033[0m" ; \
	else \
		echo "\033[37;1m[\033[31mFAIL\033[37m]\033[0m" ; \
		echo "\n$$result" ; \
		exit 1 ; \
	fi

fast:
	@make -C . FAST=1

clean :
	@echo "\033[31;1m• \033[0mRemoving object files ...\033[55G\c"
	@rm -rf $(OBJ)
	@echo "\033[37;1m[\033[32mOK !\033[37m]\033[0m"

fclean : clean
	@echo "\033[31;1m• \033[0mRemoving $(NAME) ...\033[55G\c"
	@rm -rf $(NAME)
	@echo "\033[37;1m[\033[32mOK !\033[37m]\033[0m"

mrproper: fclean

re : fclean all