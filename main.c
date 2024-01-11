#include "cub3d.h"


int main(void)
{
	t_game game;
	game.map = malloc(6 * sizeof(char *));
	game.map[0] = strdup(" 1111111111111");
	game.map[1] = strdup("10010000000001");
	game.map[2] = strdup("10101000N00001");
	game.map[3] = strdup("11010000000001");
	game.map[4] = strdup("11111111111111");
	game.map[5] = NULL;

	game.height = 5 * TILE;
	game.width = 14 * TILE;
	game.ply.x = 8 * TILE + (TILE / 2);
	game.ply.y = 2 * TILE + (TILE / 2);
	// depending on the orientation NSEW
	game.ply.angle = -M_PI_2;
	//  for debugging in 2d
	// game.mlx = mlx_init(game.width, game.height, "42Balls", false); 
	// game.img = mlx_new_image(game.mlx, game.width, game.height);
	
	// for 3d projection
	game.mlx = mlx_init(WIDTH, HEIGHT, "42Balls", false); 
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);

	// Create and display the image.
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_loop_hook(game.mlx, hook_handle, &game);
	mlx_loop(game.mlx);
}
