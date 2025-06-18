/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:40:18 by dkros             #+#    #+#             */
/*   Updated: 2025/06/18 20:05:11 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_gamefield(t_game *game)
{
	const double	half_fov = 60.0 * 0.5;
	const double	angle_start = game->dir - half_fov;
	const double	delta_angle = 60.0 / (double)SCREEN_WIDTH;
	int				screen_x;
	double			ray_angle;
	double			rad;
	double			ray_dir_x;
	double			ray_dir_y;
	bool			was_vertical;
	double			hit_x;
	double			hit_y;
	double			perp_dist;
	int				wall_h;
	double			hit_offset;
	int				tex_x;

	game->gamefield = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	screen_x = 0;
	while (screen_x < SCREEN_WIDTH)
	{
		ray_angle = angle_start + screen_x * delta_angle;
		ray_angle = fmod(ray_angle + 360.0, 360.0);
		rad = ray_angle * (M_PI / 180.0);
		ray_dir_x = cos(rad);
		ray_dir_y = sin(rad);
		perp_dist = cast_ray(game, game->x_pos, game->y_pos,
				ray_angle, 500, &was_vertical, &hit_x, &hit_y);
		if (perp_dist > 0.0)
		{
			wall_h = (int)((BLOCK_SIZE * SCREEN_HEIGHT) / perp_dist);
			if (was_vertical)
				hit_offset = fmod(hit_y, BLOCK_SIZE);
			else
				hit_offset = fmod(hit_x, BLOCK_SIZE);
			tex_x = (int)(hit_offset / BLOCK_SIZE * game->west->width);
			draw_game_line(game, wall_h, screen_x,
				tex_x, was_vertical, ray_dir_x, ray_dir_y);
		}
		screen_x++;
	}
	mlx_image_to_window(game->mlx, game->gamefield, 0, 0);
}

void	draw_background(t_game *game, int color_1, int color_2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->background = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->background)
		return ;
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

void	draw_map(t_game *game, int i, int j)
{
	game->map = mlx_new_image(game->mlx, game->map_width * BLOCK_SIZE,
			game->map_height * BLOCK_SIZE);
	while (game->two_d_map && game->two_d_map[i])
	{
		j = 0;
		while (game->two_d_map[i][j])
		{
			if (game->two_d_map[i][j] == '1')
				draw_square(game, (j * BLOCK_SIZE),
					(i * BLOCK_SIZE), BLOCK_SIZE, 0x000000FF);
			else if (game->two_d_map[i][j] == ' ')
				draw_square(game, (j * BLOCK_SIZE),
					(i * BLOCK_SIZE), BLOCK_SIZE, 0x00000000);
			else if (is_alpha(game->two_d_map[i][j]))
				draw_square(game, (j * BLOCK_SIZE),
					(i * BLOCK_SIZE), BLOCK_SIZE, 0XFFFFFFFF);
			else
				draw_square(game, (j * BLOCK_SIZE),
					(i * BLOCK_SIZE), BLOCK_SIZE, 0XFFFFFFFF);
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->mlx, game->map, 0, 0);
}

void	draw_player(t_game *game, int x, int y)
{
	int	i;
	int	j;

	game->player = mlx_new_image(game->mlx, 10, 10);
	if (!game->player)
		return ;
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

void	draw_game_line(t_game *game, int wall_height, int screen_x,
			int tex_x, bool hit_vertical, double ray_dir_x, double ray_dir_y)
{
	mlx_image_t	*tex;
	int			mid;
	int			half_h;
	int			top;
	int			bottom;
	int			y;
	int			tex_y;
	int			pixel_index;
	int			byte_offset;
	uint8_t		*p;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	px;
	uint32_t	color;

	if (hit_vertical)
	{
		if (ray_dir_x > 0)
			tex = game->west;
		else
			tex = game->east;
	}
	else
	{
		if (ray_dir_y > 0)
			tex = game->south;
		else
			tex = game->north;
	}
	if (!tex)
		return ;
	mid = SCREEN_HEIGHT / 2;
	half_h = wall_height / 2;
	top = mid - half_h;
	bottom = mid + half_h;
	y = top;
	while (y < bottom)
	{
		if (y < 0 || y > SCREEN_HEIGHT)
		{
			y++;
			continue ;
		}
		tex_y = (y - top) * tex->height / wall_height;
		pixel_index = tex_y * tex->width + tex_x;
		byte_offset = pixel_index * 4;
		p = tex->pixels;
		r = p[byte_offset];
		g = p[byte_offset + 1];
		b = p[byte_offset + 2];
		a = p[byte_offset + 3];
		px = (r << 24) | (g << 16) | (b << 8) | a;
		color = get_shaded_color(px, wall_height, hit_vertical);
		my_pixel_put(game->gamefield, screen_x, y, color);
		y++;
	}
}
