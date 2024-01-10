#include "MLX/MLX42.h"
#include <stdio.h>
#include <stdlib.h>


const int TILE_SIZE = 32;
const int MAP_NUM_ROWS = 11;
const int MAP_NUM_COLS = 15;

const int WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const int WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;


typedef struct s_player {
	int x, y;
} t_player;
typedef struct s_game {
	char **map;
	t_player player;
} t_game;

int main()
{
	t_game game;
	game.map = malloc();
}



