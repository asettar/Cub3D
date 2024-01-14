#include "../cub3D.h"



void	graphic_handle(t_map *map)
{
	t_game game;
	game.map = map->map;
	game.width = map->width * TILE;
	game.height = map->height * TILE;
	game.ply.x = map->x * TILE + TILE / 2;
	game.ply.y = map->y * TILE + TILE / 2;
	game.floor_color = map->f.value;
	game.ceil_color = map->c.value;
	if (map->orientation == 'N')
		game.ply.angle = -M_PI / 2;
	else if (map->orientation == 'S')
		game.ply.angle = M_PI / 2;
	else if (map->orientation == 'E')
		game.ply.angle = 0;
	else
		game.ply.angle = M_PI;


	// mlx init 
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub", false); 
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);


	// Create and display the image.
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_loop_hook(game.mlx, hook_handle, &game);
	mlx_loop(game.mlx);
	

}
