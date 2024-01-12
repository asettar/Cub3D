#include "cub3D.h"

void	move_player(t_game *game, double newy, double newx)
{
	if (game->map[(int)(newy / TILE)][(int)(newx / TILE)] != '1' &&
	 	game->map[(int)((newy + 3.0) / TILE)][(int)((newx) / TILE)] != '1' &&
	 	game->map[(int)((newy - 3.0) / TILE)][(int)((newx) / TILE)] != '1' && 
	 	game->map[(int)((newy) / TILE)][(int)((newx - 3.0) / TILE)] != '1' &&
	 	game->map[(int)((newy) / TILE)][(int)((newx + 3.0) / TILE)] != '1')
		game->ply.x = newx, game->ply.y = newy;
}


void	hook_handle(void *data)
{
	t_game *game = data;

	double newx = game->ply.x;
	double newy = game->ply.y;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)){
		//free
		exit(1);
	}

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		// printf("%d : %d\n", game->ply.x, game->ply.y);
		newx += cos(game->ply.angle) * SPEED;
		newy += sin(game->ply.angle) * SPEED;
		// printf("%d : %d||\n", game->ply.x, game->ply.y);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		newx -= cos(game->ply.angle) * SPEED;
		newy -= sin(game->ply.angle) * SPEED;
	}
	game->ply.angle += mlx_is_key_down(game->mlx, MLX_KEY_LEFT) * -0.05 + 
		mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) * 0.05;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		newx += sin(game->ply.angle) * SPEED;
		newy -= cos(game->ply.angle) * SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		newx -= sin(game->ply.angle) * SPEED;
		newy += cos(game->ply.angle) * SPEED;
	}
	move_player(game, newy, newx);
	// draw_map(game);
	cast_rays(game);
}
