#include "cub3d.h"

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
