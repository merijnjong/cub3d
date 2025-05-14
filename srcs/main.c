/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
/*   Updated: 2025/05/14 18:22:40 by dkros            ###   ########.fr       */
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
	game->dir = 270;
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

	(void)(color);
	(void)(img);
	(void)(sy);
	(void)(sx);
	(void)(err);
	(void)(e2);


	// while (1)
	// {
	// 	// my_pixel_put(img, x1, y1, color);
	// 	if (x1 == x2 && y1 == y2)
	// 		break;
	// 	e2 = 2 * err;
	// 	if (e2 > -dy)
	// 	{
	// 		err -= dy;
	// 		x1 += sx;
	// 	}
	// 	if (e2 < dx)
	// 	{
	// 		err += dx;
	// 		y1 += sy;
	// 	}
	// }
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

bool is_wall(t_game *g, int px, int py)
{
    int map_x = px / BLOCK_SIZE;
    int map_y = py / BLOCK_SIZE;

    if (!in_bounds(g, map_x, map_y)) 
        return true;
    return (g->two_d_map[map_y][map_x] == '1');
}

double cast_ray(t_game *game, int start_x, int start_y, double angle_deg, int max_distance, bool *hit_vertical)
{
	double rayAngle = fmod(angle_deg * (M_PI/180.0), 2*M_PI);
    if (rayAngle < 0)
		rayAngle += 2*M_PI;
	
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    int mapX = start_x / BLOCK_SIZE;
    int mapY = start_y / BLOCK_SIZE;

    double deltaDistX = fabs(1.0 / rayDirX) * BLOCK_SIZE;
    double deltaDistY = fabs(1.0 / rayDirY) * BLOCK_SIZE;

    int stepX, stepY;
    double sideDistX, sideDistY;
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = ((start_x / (double)BLOCK_SIZE) - mapX) * deltaDistX;
    }
    else
    {
        stepX = +1;
        sideDistX = (mapX + 1.0 - (start_x / (double)BLOCK_SIZE)) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = ((start_y / (double)BLOCK_SIZE) - mapY) * deltaDistY;
    }
    else
    {
        stepY = +1;
        sideDistY = (mapY + 1.0 - (start_y / (double)BLOCK_SIZE)) * deltaDistY;
    }

    bool side;
    while (1)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX    += stepX;
            side    = true;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY    += stepY;
            side    = false;
        }

        if (!in_bounds(game, mapX, mapY) || game->two_d_map[mapY][mapX] == '1')
            break;
    }

    double perpDist = side
        ? (sideDistX - deltaDistX)
        : (sideDistY - deltaDistY);

    if (perpDist > (double)max_distance)
        return -1.0;

    if (hit_vertical)
        *hit_vertical = side;
    return perpDist;
}

int get_color_from_distance(int len, int color, bool vertical)
{
	int red;
	int green;
	int blue;
	int new_color;
	double shade;

	red = (color >> 24) & 0xFF;
	green = (color >> 16) & 0xFF;
	blue = (color >> 8) & 0xFF;

	shade = 1.0 - ((500.0 / len) * 0.03);

	if (shade < 0.0)
		shade = 0.0;
	if (shade > 1.0)
		shade = 1.0;

	if (vertical)
        shade *= 0.9;

	red = (int)(red * shade);
	green = (int)(red * shade);
	blue = (int)(red * shade);

	new_color = (red << 24) | (green << 16) | (blue << 8) | 0xFF;
	return (new_color);
}

void draw_game_line(t_game *game, int wall_height, int x, bool hit_vertical)
{
	int y;
	int color;
    int mid    = SCREEN_HEIGHT / 2;
    int halfH  = wall_height / 2;
    int top    = mid - halfH;
    int bottom = top + wall_height;

    if (top < 0)
		top = 0;
    if (bottom > SCREEN_HEIGHT)
		bottom = SCREEN_HEIGHT;

	color = get_color_from_distance(wall_height, 0xFFFFFFFF, hit_vertical);

	y = top;
	while (y < bottom)
	{
		my_pixel_put(game->gamefield, x, y, color);
		y++;
	}
}


void draw_player(t_game *game, int x, int y, int color)
{
	int i;
	int j;

	game->player = mlx_new_image(game->mlx, 10, 10);
	if (!game->player)
		return;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_pixel_put(game->player, (0 + j), (0 + i), color);
			j++;
		}
		i++;
	}

	int d = 0;
	
	game->gamefield = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	
    double half_fov = 60.0 * 0.5;
    double angle_start = game->dir - half_fov;
    double delta_angle = 60.0 / (double)SCREEN_WIDTH;
	
	while (d < SCREEN_WIDTH)
	{
		double ray_angle = angle_start + d * delta_angle;
        ray_angle = fmod(ray_angle + 360.0, 360.0);

        bool was_vertical;
        double perpDist = cast_ray(game, game->x_pos, game->y_pos, ray_angle, 500, &was_vertical);
        if (perpDist > 0.0)
        {
            int wall_h = (int)((BLOCK_SIZE * SCREEN_HEIGHT) / perpDist);
            draw_game_line(game, wall_h, d, was_vertical);
        }
		d++;
	}

	mlx_image_to_window(game->mlx, game->gamefield, 0, 0);
	mlx_image_to_window(game->mlx, game->player, x, y);
}

void draw_background(t_game *game, int color_1, int color_2)
{
	int i, j;

	i = 0;
	j = 0;
	game->background = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->background)
		return;

	while (i < (SCREEN_HEIGHT / 2))
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			my_pixel_put(game->background, j, i, color_1);
			j++;
		}
		i++;
	}

	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			my_pixel_put(game->background, j, i, color_2);
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->mlx, game->background, 0, 0);
}

bool is_alpha(char c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return true;
	return false;
}

void set_player_position(t_game *game, char c, int i, int j)
{
	if (c == 'N')
		game->dir = 270;
	else if (c == 'S')
		game->dir = 90;
	else if (c == 'W')
		game->dir = 180;
	else if (c == 'E')
		game->dir = 0;
	else
	{
		printf("Invalid character found\n");
		exit_game(game);
	}
	game->x_pos = i * BLOCK_SIZE;
	game->y_pos = j * BLOCK_SIZE;
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
	
	draw_background(&game, 0x87CEEBFF, 0x777777FF);
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
			else if (is_alpha(game.two_d_map[i][j]))
			{
				set_player_position(&game, game.two_d_map[i][j], i, j);
				draw_square(&game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0XFFFFFFFF);
			}
			else
			{
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
