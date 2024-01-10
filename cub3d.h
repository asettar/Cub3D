#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#define WIDTH 700
#define HEIGHT 450
#define SPEED 4
#define FOV M_PI / 3.0
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


