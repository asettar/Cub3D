#include "cub3d.h"



void	move_player(t_game *game, double newy, double newx)
{
	if (game->map[(int)(newy / TILE)][(int)(newx / TILE)] != '1' &&
	 	game->map[(int)((newy + 3.0) / TILE)][(int)((newx) / TILE)] != '1' &&
	 	game->map[(int)((newy - 3.0) / TILE)][(int)((newx) / TILE)] != '1' && 
	 	game->map[(int)((newy) / TILE)][(int)((newx - 3.0) / TILE)] != '1' &&
	 	game->map[(int)((newy) / TILE)][(int)((newx + 3.0) / TILE)] != '1')
		game->ply.x = newx, game->ply.y = newy;
}

double horizantal_intersection(t_game *game, double angle)
{
	// double distance = 0.0;	
	double xinter, yinter;
	yinter = floor(game->ply.y / TILE) * TILE;
	if (sin(game->ply.angle) > 0) yinter += TILE;
	else yinter -= 0.000001;
	xinter = (yinter - game->ply.y) / tan(angle) + game->ply.x;
	// draw_point(game, xinter, yinter);
	// printf("%f : %f   ||  ", game->ply.y, game->ply.x);
	// printf("%f : %f\n", yinter, xinter);

	double ystep = TILE;
	if (sin(angle) < 0)
		ystep *= -1;
	double xstep = ystep / tan(angle);
	// printf("%f : %f\n", yinter, xinter);
	while (1)
	{
		if (xinter <= 0 || xinter >= game->width || yinter <= 0 || yinter >= game->height)
			break;
		// printf("%f : %f\n", yinter, xinter);

		if (game->map[(int)(yinter/ TILE)][(int)(xinter / TILE)] == '1'){
			// printf("%f : %f || \n", yinter, xinter);
			// draw_point(game, xinter, yinter);
			return sqrt(pow(xinter - game->ply.x, 2) + pow(yinter - game->ply.y, 2));
		}
		xinter += xstep;
		yinter += ystep;
	}
	return INT_MAX;
}

double vertical_intersection(t_game *game, double angle)
{
	double xinter, yinter;
	xinter = floor(game->ply.x / TILE) * TILE;
	if (cos(angle) > 0) xinter += TILE;
	else xinter -= 0.000001;
	yinter = (xinter - game->ply.x) * tan(angle) + game->ply.y;

	// draw_point(game, xinter, yinter);
	// printf("%f : %f   ||  ", game->ply.y, game->ply.x);
	// printf("%f : %f\n", yinter, xinter);

	double xstep = TILE;
	if (cos(angle) < 0)
		xstep *= -1;
	double ystep = xstep * tan(angle);
	// printf("%f : %f\n", yinter, xinter);
	while (1)
	{
		if (xinter <= 0 || xinter >= game->width || yinter <= 0 || yinter >= game->height)
			break;
		// printf("%f : %f\n", yinter, xinter);

		if (game->map[(int)(yinter/ TILE)][(int)(xinter / TILE)] == '1'){
			printf("%f : %f || \n", yinter, xinter);
			// draw_point(game, xinter, yinter);
			return sqrt(pow(xinter - game->ply.x, 2) + pow(yinter - game->ply.y, 2));
		}
		xinter += xstep;
		yinter += ystep;
	}
	return INT_MAX;
}

void	cast_rays(t_game *game)
{
	double distance;
	double start_angle = game->ply.angle - FOV / 2.0;
	double end_angle = game->ply.angle + FOV / 2.0;
	while (start_angle < end_angle)
	{
		distance = fmin(horizantal_intersection(game, start_angle),
			vertical_intersection(game, start_angle));
		start_angle += M_PI / 180.0;
	}
}
void	hook_handle(void *data)
{
	t_game *game = data;

	// if (sin(game->ply.angle) <= 0)
	// 	game->ply.verti_move = 1;
	// else game->ply.verti_move = -1;
	// if (cos(game->ply.angle) >= 0)
	// 	game->ply.horiz_move = 1;
	// else game->ply.horiz_move = -1;
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
	draw_map(game);
	cast_rays(game);
}

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
	game.mlx = mlx_init(game.width, game.height, "42Balls", false);

	// Create and display the image.
	game.img = mlx_new_image(game.mlx, game.width, game.height);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_loop_hook(game.mlx, hook_handle, &game);
	mlx_loop(game.mlx);
}
