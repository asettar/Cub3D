CC		 =  cc
CFLAGS	 =  -Wall -Werror -Wextra -O3 -ffast-math
NAME	 =  cub3D
MLX      =  MLX/libmlx42.a
MLXFLAGS =  -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE  =  -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
LIB      =  -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib


SRCS	= main.c mlx.c draw_files.c player_mouvements.c casting.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS)  $(MLX) $(LIB) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
re: fclean all
