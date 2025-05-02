/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
/*   Updated: 2025/05/02 15:46:58 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	file_to_map(t_game *game, char *filename)
{
	char	*temp;
	char	*map;
	int		fd;

	map = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(MAP_ERROR);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		map = ft_strjoin2(map, temp);
		free(temp);
	}
	close(fd);
	game->two_d_map = ft_split(map, '\n');
	free(map);
}

void	init(t_game *game)
{
	game->x_pos = 100;
	game->y_pos = 100;
	game->dir = 180;
	game->map_width = 0;
	game->map_height = 0;
	game->two_d_map = NULL;
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", false);
	if (!game->mlx)
	{
		ft_printf("Failed to initialize graphics library\n");
		exit(EXIT_FAILURE);
	}
	game->roof = NULL;
	game->floor = NULL;
	game->north = NULL;
	game->east = NULL;
	game->south = NULL;
	game->west = NULL;
}


void	my_pixel_put(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		mlx_put_pixel(img, x, y, color);
}


double draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		my_pixel_put(img, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
	double len = sqrt((double)(pow(dx, 2) + pow(dy, 2)));
	return (len);
}

void draw_line_angle(mlx_image_t *img, int x, int y, int length, double angle_deg, int color)
{
	double angle_rad;
	angle_rad = angle_deg * (M_PI / 180.0);

	int x_end;
	int y_end;

	x_end = x + (int)(length * cos(angle_rad));
	y_end = y + (int)(length * sin(angle_rad));

	draw_line(img, x, y, x_end, y_end, color);
}

mlx_image_t *draw_square(t_game *data, int x, int y, int size, int color)
{
	int i;
	int j;


	(void)color;
	data->img = mlx_new_image(data->mlx, size, size);
	if (!data->img)
	return (NULL);
	i = 0;
	while (i < (size - 1))
	{
		j = 0;
		while (j < (size - 1))
		{
			my_pixel_put(data->img, j, i, color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->img, x, y);
	return (data->img);
}

bool in_bounds(t_game *g, int x, int y)
{
    if (y < 0 || y >= g->map_height) 
        return false;
    if (x < 0 || x >= (int)ft_strlen(g->two_d_map[y]))
        return false;
    return true;
}

// Updated is_wall:
bool is_wall(t_game *g, int px, int py)
{
    int map_x = px / BLOCK_SIZE;
    int map_y = py / BLOCK_SIZE;
    // treat out-of-bounds as wall
    if (!in_bounds(g, map_x, map_y)) 
        return true;
    return (g->two_d_map[map_y][map_x] == '1');
}

// bool cast_ray(t_game *game, int start_x, int start_y, double angle_deg, int max_distance, int *wall_hit_x, int *wall_hit_y)
// {
// 	double angle_rad = angle_deg * (M_PI / 180.0);
// 	double step_size = 5.0;
// 	double current_distance = 0.0;

// 	double ray_x = (double)start_x;
// 	double ray_y = (double)start_y;

// 	while (current_distance < max_distance)
// 	{
// 		ray_x += cos(angle_rad) * step_size;
// 		ray_y += sin(angle_rad) * step_size;
// 		current_distance += step_size;

// 		int check_x = (int)ray_x;
// 		int check_y = (int)ray_y;

// 		if (is_wall(game, check_x, check_y))
// 		{
// 			if (wall_hit_x) *wall_hit_x = check_x;
// 			if (wall_hit_y) *wall_hit_y = check_y;
// 			return true;
// 		}
// 	}
// 	return false;
// }

bool cast_ray(t_game *game, int start_x, int start_y, double angle_deg, int max_distance, int *wall_hit_x, int *wall_hit_y)
{
	double angle_rad = fmod(angle_deg * (M_PI/180.0), 2*M_PI);
	if (angle_rad < 0) angle_rad += 2*M_PI;

	double dirX =  cos(angle_rad);
	double dirY =  sin(angle_rad);

	double traveled = 0.0;
	const double BLOCK = (double)BLOCK_SIZE;

	while (traveled < (double)max_distance)
	{
		if (is_wall(game, start_x, start_y))
		{
			if (wall_hit_x)
				*wall_hit_x = start_x;
			if (wall_hit_y)
				*wall_hit_y = start_y;
			return true;
		}

		int modX = start_x % BLOCK_SIZE;  
		int modY = start_y % BLOCK_SIZE;

		if (modX < 0)
			modX += BLOCK_SIZE;
		if (modY < 0)
			modY += BLOCK_SIZE;

		double distVert  = (dirX > 0) ? (BLOCK - modX) / dirX : (-modX) / dirX;
		double distHoriz = (dirY > 0) ? (BLOCK - modY) / dirY : (-modY) / dirY;

		double step = (fabs(distVert) < fabs(distHoriz)) ? distVert : distHoriz;

		int deltaX = (int)round(dirX * step);
		int deltaY = (int)round(dirY * step);

		if (deltaX == 0 && deltaY == 0)
		{
			deltaX = (dirX > 0 ? 1 : (dirX < 0 ? -1 : 0));
			deltaY = (dirY > 0 ? 1 : (dirY < 0 ? -1 : 0));
		}

		start_x  += deltaX;
		start_y  += deltaY;
		traveled += sqrt((double)deltaX*deltaX + (double)deltaY*deltaY);
	}

	return false;
}


void draw_game_line(t_game *game, int len, int index)
{
	int i;
	int j;
	int color;

	color = 0xFFFFFFFF - (500 / len) * 8;
	if (!game->gamefield)
		return;

	int start_y = (750 - len) / 2;
	if (start_y < 0) start_y = 0;
	
	i = 0;
	while (i < len && (start_y + i) < 750)
	{
		j = 0;
		while (j < (1000 /60))
		{
			my_pixel_put(game->gamefield, ((1000 /60) * index + j), start_y + i, color);
			j++;
		}
		i++;
	}
}

void draw_player(t_game *game, int x, int y, int color)
{
	int i;
	int j;

	game->player = mlx_new_image(game->mlx, 500, 500);
	if (!game->player)
		return;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 16)
		{
			my_pixel_put(game->player, (242 + j), (242 + i), color);
			j++;
		}
		i++;
	}

	int d = -30;
	int wall_hit_x;
	int wall_hit_y;
	int player_origin_x = 250;
	int player_origin_y = 250;
	
	game->gamefield = mlx_new_image(game->mlx, 1000, 750);
	
	while (d < 30)
	{
		double ray_angle = fmod((game->dir + d + 360), 360);

		if (cast_ray(game, game->x_pos + player_origin_x, game->y_pos + player_origin_y, ray_angle, 500, &wall_hit_x, &wall_hit_y))
		{
			int local_wall_x = wall_hit_x - game->x_pos;
			int local_wall_y = wall_hit_y - game->y_pos;

			double len = draw_line(game->player, player_origin_x, player_origin_y, local_wall_x, local_wall_y, 0xFF0000FF);

			double corrected_len = len * cos(d * M_PI / 180.0);
			int wall_height = (int)((BLOCK_SIZE * 750) / corrected_len);
			
			draw_game_line(game, wall_height, d + 30);
		}
		else
			draw_line_angle(game->player, player_origin_x, player_origin_y, 249, ray_angle, 0xFF0000FF);
		d++;
	}

	mlx_image_to_window(game->mlx, game->gamefield, 800, 0);
	mlx_image_to_window(game->mlx, game->player, x, y);
}

void draw_background(t_game *game, int color_1, int color_2)
{
	int i, j;

	i = 0;
	j = 0;
	game->background = mlx_new_image(game->mlx, 1000, 750);
	if (!game->background)
		return;
	
	while (i < 375)
	{
		j = 0;
		while (j < 1000)
		{
			my_pixel_put(game->background, j, i, color_1);
			j++;
		}
		i++;
	}

	while (i < 750)
	{
		j = 0;
		while (j < 1000)
		{
			my_pixel_put(game->background, j, i, color_2);
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->mlx, game->background, 800, 0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!argv[1] || argc > 2)
	{
		ft_printf(INPUT_ERROR);
		exit(1);
	}
	init(&game);
	file_to_map(&game, argv[1]);
	while (game.two_d_map[game.map_height])
    	game.map_height++;
	print_dbl_ptr(game.two_d_map);

	int i;
	int j;

	i = 0;
	
	draw_background(&game, 0xFF1166FF, 0x55FF55FF);
	while (game.two_d_map && game.two_d_map[i])
	{
		j = 0;
		while (game.two_d_map[i][j])
		{
			if (game.two_d_map[i][j] == '1') {
				draw_square(&game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0x000000FF);
			}
			else if (game.two_d_map[i][j] == '2') {
				draw_square(&game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0XFF0000FF);
			}
			else {
				draw_square(&game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0XFFFFFFFF);
			}
			j++;
		}
		i++;
	}

	draw_player(&game, game.x_pos, game.y_pos, 0x00FFFFFF);

	if (game.mlx)
	{
		mlx_key_hook(game.mlx, (void *)&ft_hooks, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
