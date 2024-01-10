#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "MLX/MLX42.h"


#define WIDTH 700
#define HEIGHT 450
#define SPEED 4
#define FOV M_PI / 3.0
#define TILE 64.0


typedef struct s_player
{
	double x;
	double y;
	double wall_hitx;
	double wall_hity;
	double angle;
} t_player;

typedef struct s_game
{
	char **map;
	int height;
	int width;
	t_player	ply;
	mlx_image_t* img;
	mlx_t *mlx;
}	t_game;


void	draw_point(t_game *game, double x, double y);
void	draw_line(t_game *game);
void	draw_rectangle(t_game *game, int y, int x, int color);
void	draw_map(t_game *game);
void	hook_handle(void *data);
void	cast_rays(t_game *game);
