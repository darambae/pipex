CC = gcc
NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror
SRC = ft_printf.c ft_print_char.c ft_print_hex.c ft_print_int.c \
	ft_print_pointer.c ft_print_str.c ft_print_unsigned.c
OBJ = $(SRC:.c=.o)
LIBFT = ./libft/libft.a

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	cp ./libft/libft.a $(NAME)
	ar -rcs $@ $^
$(LIBFT):
	make -C ./libft all
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	make -C ./libft clean
	rm -f $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
