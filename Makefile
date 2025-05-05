NAME = cub3D

CC = cc 
# CFLAGS = -Wall -Wextra -Werror 

SRC = main.c\
	parsing/parsing.c\
	parsing/get_next_line.c\
	parsing/get_next_line_utils.c\
	parsing/data_extraction.c\
	parsing/map_utils.c\
	parsing/parse_elements.c\
	parsing/take_map.c\
	parsing/verify_utils.c\
	parsing/map_parsing.c\
	raycast/init_map.c\
	


OBJ = $(SRC:.c=.o)

# Add libft directory
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

# Compile libft before compiling cub3D
$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz -Llibft -lft -o cub3D

%.o : %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -I$(LIBFT_DIR) -O3 -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
.SECONDARY :
