NAME = pipex
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
FILE = outfile
GET_NEXT_LINE_DIR = get_next_line
GET_NEXT_LINE = $(wildcard $(GET_NEXT_LINE_DIR)/*.c)
SRC = pipex.c parsing.c pipex_bonus.c ft_split_special.c
OBJ = $(SRC:.c=.o) $(GET_NEXT_LINE:.c=.o)

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./libft
	
clean:
	$(MAKE) clean -C ./libft
	@$(RM) -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C ./libft 
	@$(RM) -f $(NAME)
	@$(RM) -f $(FILE)

re: fclean all

.PHONY: all clean fclean re
