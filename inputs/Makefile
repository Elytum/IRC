NAME = get_lines

SOURCES =	ft_arrows.c				\
			ft_arrows2.c			\
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

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(LIBNAME) $(OBJ)
	@ranlib $(LIBNAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c  $(INC) $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(LIBNAME)

re: fclean all