#include "../cub3D.h"

void horizantal_intersection(t_game *game, t_ray *ray)
{
	// double distance = 0.0;
	double xinter, yinter;
	yinter = floor(game->ply.y / TILE) * TILE;
	if (sin(ray->angle) > 0) yinter += TILE;
	else yinter -= 0.0000001;
	xinter = (yinter - game->ply.y) / tan(ray->angle) + game->ply.x;
	// draw_point(game, xinter, yinter);
	// printf("%f : %f   ||  ", game->ply.y, game->ply.x);
	// printf("%f : %f\n", yinter, xinter);

	double ystep = TILE;
	if (sin(ray->angle) < 0)
		ystep *= -1;
	double xstep = ystep / tan(ray->angle);
	// printf("%f : %f\n", yinter, xinter);
	while (1)
	{
		if (xinter <= 0 || xinter >= game->width || yinter <= 0 || yinter >= game->height)
			break;
		// printf("%f : %f\n", yinter, xinter);

		if (game->map[(int)((yinter)/ TILE)][(int)(xinter / TILE)] == '1'){
			// printf("%f : %f || \n", yinter, xinter);
			ray->wall_hitx = xinter;
			ray->wall_hity = yinter;
			ray->horizantal_intersection = 1;
			ray->distance_to_wall = sqrt(pow(xinter - game->ply.x, 2) + pow(yinter - game->ply.y, 2));
			// draw_point(game, ray->wall_hitx, ray->wall_hity);
			return ;
		}
		xinter += xstep;
		yinter += ystep;
	}
	ray->distance_to_wall = INT_MAX;
}

void vertical_intersection(t_game *game, t_ray *ray)
{
	double xinter, yinter;
	xinter = floor(game->ply.x / TILE) * TILE;
	if (cos(ray->angle) > 0) xinter += TILE;
	else xinter -= 0.0000001;
	yinter = (xinter - game->ply.x) * tan(ray->angle) + game->ply.y;

	// draw_point(game, xinter, yinter);
	// printf("%f : %f   ||  ", game->ply.y, game->ply.x);
	// printf("%f : %f\n", yinter, xinter);

	double xstep = TILE;
	if (cos(ray->angle) < 0)
		xstep *= -1;
	double ystep = xstep * tan(ray->angle);
	// printf("%f : %f\n", yinter, xinter);
	while (1)
	{
		if (xinter <= 0 || xinter >= game->width || yinter <= 0 || yinter >= game->height)
			break;
		// printf("%f : %f\n", yinter, xinter);

		if (game->map[(int)(yinter / TILE)][(int)(xinter / TILE)] == '1'){
			// printf("%f : %f || \n", yinter, xinter);
			// draw_point(game, xinter, yinter);
			double dis = sqrt(pow(xinter - game->ply.x, 2) + pow(yinter - game->ply.y, 2));
			if (ray->distance_to_wall > dis)
			{
				ray->distance_to_wall = dis;
				ray->wall_hitx = xinter;
				ray->wall_hity = yinter;
				ray->horizantal_intersection = 0;

			}
			// if (xinter >= 10 && xinter < game->width - 10 && yinter >= 10 && yinter < game->height - 10) 
			// 	draw_point(game, xinter, yinter);

			return ;
		}
		xinter += xstep;
		yinter += ystep;
	}
}

// void	cast_rays(t_game *game)
// {
// 	double distance;
// 	double start_angle = game->ply.angle - FOV / 2.0;
// 	double end_angle = game->ply.angle + FOV / 2.0;
// 	while (start_angle < end_angle)
// 	{
// 		distance = fmin(horizantal_intersection(game, start_angle),
// 			vertical_intersection(game, start_angle));
// 		start_angle += M_PI / 180.0;
// 	}
// }

uint32_t	get_texture_color(mlx_texture_t *texture, t_ray *ray, double wall_height, double y)
{
	int texture_offset_x;
	int texture_offset_y;

	int wall_start = ((double)HEIGHT / 2.0) - (wall_height / 2.0);
	if (ray->horizantal_intersection)
		texture_offset_x = fmod(ray->wall_hitx, TILE) * ((double)texture->width / TILE);
		// texture_offset_x = fmod(ray->wall_hitx / TILE * (double)texture->width , TILE);
	else 
		// texture_offset_x = fmod(ray->wall_hity / TILE * (double)texture->width , TILE);
		texture_offset_x = fmod(ray->wall_hity, TILE) * ((double)texture->width / TILE);
	
	texture_offset_y = (y - wall_start) * (double)texture->height / wall_height;

	unsigned int index = texture_offset_y * texture->width * texture->bytes_per_pixel + texture_offset_x * texture->bytes_per_pixel;

	uint8_t *pixels = texture->pixels;
	// if (index >= texture->width * texture->height * texture->bytes_per_pixel)
	// {
	// 	printf("wallhit : %f %f ::\n", ray->wall_hitx, ray->wall_hity);
	// 	printf("textures : %d %d ::\n", texture_offset_x, texture_offset_y);
	// 	printf("index : %d || len = %u \n", index, texture->width * texture->height * texture->bytes_per_pixel);
	// 	exit(1);
	// }
	uint32_t color = pixels[index] << 24 | pixels[index + 1] << 16 | pixels[index + 2] << 8 | pixels[index + 3];
	return color;

}

void	project_wall(t_game *game, int x, t_ray *ray)
{
	double wall_height;

	wall_height = TILE * ((double)(WIDTH / 2.0) / tan(FOV / 2.0)) / ray->distance_to_wall;
	int start_y = (double)HEIGHT / 2.0 - (wall_height / 2.0);
	if (start_y < 0) start_y = 0;
	int end_y = ((double)HEIGHT / 2.0) + (wall_height / 2.0);
	if (end_y >= HEIGHT) end_y = HEIGHT - 1;
	// printf("wall height = %f\n %d %d |, x = %d ||\n", wall_height, start_y, end_y, x);
	int y = 0;
	for(; y < start_y; y++)
		mlx_put_pixel(game->img, x, y, game->ceil_color);
	for(; y <= end_y; y++)
	{
		// mlx_put_pixel(game->img, x, y, 0xFF0024FF);
		mlx_put_pixel(game->img, x, y, get_texture_color(game->texture, ray, wall_height, y));
	}
	for(; y < HEIGHT; y++)
		mlx_put_pixel(game->img, x, y, game->floor_color);
}

void	cast_rays(t_game *game)
{
	t_ray ray;
	ray.angle = game->ply.angle - FOV / 2.0;
	int x = 0;
	while (x < WIDTH)
	{
		horizantal_intersection(game, &ray),
		vertical_intersection(game, &ray);
		// printf("%f\n", distance);
		ray.distance_to_wall *= cos(ray.angle - game->ply.angle); 
		project_wall(game, x, &ray);
		ray.angle += FOV / (double)WIDTH;
		x++;
	}
}
