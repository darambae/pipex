NAME = pipex
#BONUS_NAME = checker

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
#GET_NEXT_LINE_DIR = get_next_line
#GET_NEXT_LINE = $(wildcard $(GET_NEXT_LINE_DIR)/*.c)
SRC = pipex.c parsing.c
#BONUS = $(BONUS_NAME).c push_swap.c
#SRCS_BONUS = $(BONUS) $(GET_NEXT_LINE)
OBJ = $(SRC:.c=.o)
#OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft

#$(BONUS_NAME) : $(LIBFT) $(OBJ_COMMON) $(OBJ_BONUS)
        #$(CC) $(CFLAGS) -o $@ $^ -L./libft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./libft

#bonus: $(BONUS_NAME)

clean:
	$(MAKE) clean -C ./libft
	@$(RM) -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C ./libft 
	@$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
