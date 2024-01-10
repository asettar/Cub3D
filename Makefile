CC		= cc
CFLAGS	= -Wall -Werror -Wextra -O3 -ffast-math
NAME	= cub3D
MLX = MLX/libmlx42.a
FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
LIB = -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib


SRCS	= main.c mlx.c
OBJS	= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	# make -s -C $(LIB_FT)
	$(CC) $(CFLAGS) $(FLAG_MLX) $(OBJS)  $(MLX) $(LIB) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
clean:
	# make clean -s -C $(LIB_FT)
	rm -f $(OBJS)

# mini:
	# cc -O3 -ffast-math -framework Cocoa -framework OpenGL -framework IOKit -lglfw $(MLX) $(LIB) mini_cub3D.c -o mini_cub3D
# 
fclean: clean
	make fclean -s -C $(LIB_FT)
	rm -f $(NAME)
	rm -f $(NAME_B)

re: fclean all
