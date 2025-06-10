/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
/*   Updated: 2025/06/10 16:32:31 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	my_pixel_put(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		mlx_put_pixel(img, x, y, color);
}

double get_dist(int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	double len = sqrt((double)(pow(dx, 2) + pow(dy, 2)));
	return (len);
}

void draw_line_angle(int x, int y, int length, double angle_deg)
{
	double angle_rad;
	angle_rad = angle_deg * (M_PI / 180.0);

	int x_end;
	int y_end;

	x_end = x + (int)(length * cos(angle_rad));
	y_end = y + (int)(length * sin(angle_rad));

	get_dist(x, y, x_end, y_end);
}

mlx_image_t *draw_square(t_game *data, int x, int y, int size, int color)
{
	int i;
	int j;

	if (!data->map)
	return (NULL);
	i = 0;
	while (i < (size - 1))
	{
		j = 0;
		while (j < (size - 1))
		{
			my_pixel_put(data->map, j + x, i + y, color);
			j++;
		}
		i++;
	}
	return (data->map);
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

double cast_ray(t_game *game, int start_x, int start_y, double angle_deg, int max_distance, bool *hit_vertical, double *hit_x, double *hit_y)
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
            mapX += stepX;
            side = true;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = false;
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

    if (hit_x)
        *hit_x = start_x + rayDirX * perpDist;

    if (hit_y)
        *hit_y = start_y + rayDirY * perpDist;

    return perpDist;
}

static double clamp(double v, double lo, double hi) {
    return v < lo ? lo : v > hi ? hi : v;
}

// returns a shaded RGBA color, preserving alpha
static uint32_t get_shaded_color(uint32_t pixel, int dist, bool hit_vertical) {
    // MLX42 stores colors as 0xRRGGBBAA :contentReference[oaicite:0]{index=0}
    uint8_t r = (pixel >> 24) & 0xFF;
    uint8_t g = (pixel >> 16) & 0xFF;
    uint8_t b = (pixel >>  8) & 0xFF;
    uint8_t a =  pixel        & 0xFF;

    // simple distance‐based darkening
    double shade = 1.0 - (dist * 0.03 / 500.0);
    shade = clamp(shade, 0.0, 1.0);
    if (hit_vertical)
        shade *= 0.9;

    r = (uint8_t)(r * shade);
    g = (uint8_t)(g * shade);
    b = (uint8_t)(b * shade);

    return (r<<24) | (g<<16) | (b<<8) | a;
}

void draw_game_line(t_game *game, int wall_height, int screen_x, int tex_x, bool hit_vertical, double rayDirX, double rayDirY)
{
    mlx_image_t *tex;
    if (hit_vertical) {
        tex = (rayDirX > 0 ? game->west : game->east);
    } else {
        tex = (rayDirY > 0 ? game->south : game->north);
    }
    if (!tex) return;

    int mid    = SCREEN_HEIGHT / 2;
    int halfH  = wall_height / 2;
    int top    = mid - halfH;
    int bottom = mid + halfH;
    if (top < 0)
		top = 0;
    if (bottom > SCREEN_HEIGHT)
		bottom = SCREEN_HEIGHT;
	int y;
	y = top;
	while (y < bottom)
	{
		int tex_y = (y - top) * tex->height / wall_height;
	
		int pixel_index = tex_y * tex->width + tex_x;
		int byte_offset = pixel_index * 4;
		uint8_t *p = tex->pixels;
	
		uint8_t r = p[byte_offset];
		uint8_t g = p[byte_offset + 1];
		uint8_t b = p[byte_offset + 2];
		uint8_t a = p[byte_offset + 3];
		uint32_t px = (r << 24) | (g << 16) | (b << 8) | a;
	
		uint32_t c = get_shaded_color(px, wall_height, hit_vertical);
		my_pixel_put(game->gamefield, screen_x, y, c);
		y++;
	}
}

void draw_gamefield(t_game *game)
{
	const double half_fov    = 60.0 * 0.5;
    const double angle_start = game->dir - half_fov;
    const double delta_angle = 60.0 / (double)SCREEN_WIDTH;
	
	game->gamefield = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    for (int screen_x = 0; screen_x < SCREEN_WIDTH; ++screen_x)
    {
        double ray_angle = angle_start + screen_x * delta_angle;
        ray_angle = fmod(ray_angle + 360.0, 360.0);
        double rad = ray_angle * (M_PI / 180.0);
        double rayDirX = cos(rad);
        double rayDirY = sin(rad);
        bool   was_vertical;
        double hit_x, hit_y;
        double perpDist = cast_ray(game, game->x_pos, game->y_pos, ray_angle, 500, &was_vertical, &hit_x, &hit_y);

        if (perpDist > 0.0)
        {
            int wall_h = (int)((BLOCK_SIZE * SCREEN_HEIGHT) / perpDist);
            double hit_offset = was_vertical ? fmod(hit_y, BLOCK_SIZE) : fmod(hit_x, BLOCK_SIZE);
            int tex_x = (int)(hit_offset / BLOCK_SIZE * game->west->width);
            draw_game_line(game, wall_h, screen_x, tex_x, was_vertical, rayDirX, rayDirY);
        }
    }
    mlx_image_to_window(game->mlx, game->gamefield, 0, 0);
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
    printf("%c", c);
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

void draw_map(t_game *game, int i, int j)
{
	game->map = mlx_new_image(game->mlx, game->map_width * BLOCK_SIZE, game->map_height * BLOCK_SIZE);
	while (game->two_d_map && game->two_d_map[i])
	{
		j = 0;
		while (game->two_d_map[i][j])
		{
			if (game->two_d_map[i][j] == '1')
				draw_square(game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0x000000FF);
			else if (game->two_d_map[i][j] == ' ')
				draw_square(game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0x00000000);
			else if (is_alpha(game->two_d_map[i][j]))
				draw_square(game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0XFFFFFFFF);
			else
				draw_square(game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0XFFFFFFFF);
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->mlx, game->map, 0, 0);
}


void draw_player(t_game *game, int x, int y)
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
			my_pixel_put(game->player, (0 + j), (0 + i), 0XFF22FFFF);
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->mlx, game->player, x, y);
}