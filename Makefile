CC		 =  cc
CFLAGS	 =  -Wall -Werror -Wextra -O3 -ffast-math
NAME	 =  cub3D
MLX      =  MLX/libmlx42.a
MLXFLAGS =  -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE  =  -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include/GLFW
LIB      =  -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib


SRCS	= main.c  \
		draw_files.c \
		player_mouvements.c \
		casting.c \
		graphic_handle.c \
		gnl/gnl_utils.c \
		gnl/gnl.c \
		lib/ft_atoi.c \
		lib/ft_printer.c \
		lib/ft_strcmp.c \
		lib/ft_memset.c \
		lib/ft_repeat.c \
		lib/ft_split.c \
		lib/ft_strtok.c \
		lib/ft_strtrim.c \
		lib/ft_strchr.c \
		utils/check_duplicated.c \
		utils/check_empty_line.c \
		utils/check_in_border.c \
		utils/check_map_errs.c \
		utils/check_textures_color.c \
		utils/exit_err.c \
		utils/fill_map.c \
		utils/insert_colors.c \
		utils/is_a_mem_player.c \
		utils/read_map.c \
		utils/read_textures.c \
		utils/set_colors.c 
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS)  $(MLX) $(LIB) -o $(NAME)

%.o: %.c cub3D.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
re : fclean all
