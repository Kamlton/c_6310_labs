NAME = matrix
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./inc

SRC_DIR = src
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/create_matrix.c \
       $(SRC_DIR)/remove_matrix.c \
       $(SRC_DIR)/print_matrix.c \
       $(SRC_DIR)/sum_matrix.c \
       $(SRC_DIR)/sub_matrix.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re