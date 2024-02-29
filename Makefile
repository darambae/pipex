NAME = push_swap
#BONUS_NAME = checker

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES)
LIBFT = libft/libft.a
SRC_DIR = srcs

GET_NEXT_LINE_DIR = get_next_line
GET_NEXT_LINE = $(wildcard $(GET_NEXT_LINE_DIR)/*.c)
INCLUDES = include
SRC = main.c push_swap.c
BONUS = $(BONUS_NAME).c push_swap.c
COMMON = algorithm.c error_handling.c \
                init_stack.c push.c reverse_rotate.c \
                rotate.c split_argv.c swap.c \
                utils_a_to_b.c utils_algorithm.c \
                utils_b_to_a.c utils_list.c
SRCS_BONUS = $(BONUS) $(GET_NEXT_LINE)
OBJ = $(SRC:.c=.o)
OBJ_COMMON = $(COMMON:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ) $(OBJ_COMMON)
        $(CC) $(CFLAGS) -o $@ $^ -L./libft -lft

$(BONUS_NAME) : $(LIBFT) $(OBJ_COMMON) $(OBJ_BONUS)
        $(CC) $(CFLAGS) -o $@ $^ -L./libft -lft

%.o: %.c
                $(CC) $(CFLAGS) -c $< -o $@


$(LIBFT):
        $(MAKE) -C ./libft

bonus: $(BONUS_NAME)

clean:
        $(MAKE) clean -C ./libft
        @$(RM) -f $(OBJ) $(OBJ_COMMON) $(OBJ_BONUS)

fclean: clean
        $(MAKE) fclean -C ./libft 
        @$(RM) -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
