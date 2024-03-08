NAME = pipex
BONUS = pipex_bonus

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
FILE = outfile
GET_NEXT_LINE_DIR = get_next_line
GET_NEXT_LINE = $(wildcard $(GET_NEXT_LINE_DIR)/*.c)
SRC_COMMON = parsing.c ft_split_special.c
SRC_MAN = pipex.c
SRC_BONUS = pipex_bonus.c main_bonus.c $(GET_NEXT_LINE)
OBJ = $(SRC_MAN:.c=.o)
OBJ_COMMON = $(SRC_COMMON:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ) $(OBJ_COMMON)
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft

$(BONUS) : $(LIBFT) $(OBJ_COMMON) $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./libft

bonus: $(BONUS)

clean:
	$(MAKE) clean -C ./libft
	@$(RM) -f $(OBJ) $(OBJ_COMMON) $(OBJ_BONUS)

fclean: clean
	$(MAKE) fclean -C ./libft 
	@$(RM) -f $(NAME) $(BONUS) $(FILE)

re: fclean all

.PHONY: all clean fclean re
