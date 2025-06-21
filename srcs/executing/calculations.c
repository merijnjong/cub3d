/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merijnjong <merijnjong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:18 by dkros             #+#    #+#             */
/*   Updated: 2025/06/21 02:45:00 by merijnjong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

bool	is_wall(t_game *game, int px, int py)
{
	int	map_x;
	int	map_y;

	map_x = px / game->block_size;
	map_y = py / game->block_size;
	if (!in_bounds(game, map_x, map_y))
		return (true);
	return (game->two_d_map[map_y][map_x] == '1');
}

double	cast_ray(t_game *game, int start_x, int start_y,
				double angle_deg, int max_distance,
				bool *hit_vertical, double *hit_x, double *hit_y)
{
	double	ray_angle;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	bool	side;
	double	perp_dist;

	ray_angle = fmod(angle_deg * (M_PI / 180.0), 2 * M_PI);
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	map_x = start_x / game->block_size;
	map_y = start_y / game->block_size;
	delta_dist_x = fabs(1.0 / ray_dir_x) * game->block_size;
	delta_dist_y = fabs(1.0 / ray_dir_y) * game->block_size;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = ((start_x / (double)game->block_size) - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - (start_x / (double)game->block_size)) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = ((start_y / (double)game->block_size) - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - (start_y / (double)game->block_size)) * delta_dist_y;
	}
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = true;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = false;
		}
		if (!in_bounds(game, map_x, map_y)
			|| game->two_d_map[map_y][map_x] == '1')
			break ;
	}
	if (side)
		perp_dist = side_dist_x - delta_dist_x;
	else
		perp_dist = side_dist_y - delta_dist_y;
	if (perp_dist > (double)max_distance)
		return (-1.0);
	if (hit_vertical)
		*hit_vertical = side;
	if (hit_x)
		*hit_x = start_x + ray_dir_x * perp_dist;
	if (hit_y)
		*hit_y = start_y + ray_dir_y * perp_dist;
	return (perp_dist);
}

double	clamp(double v, double lo, double hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

uint32_t	get_shaded_color(uint32_t pixel, int dist, bool hit_vertical)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
	double	shade;

	r = (pixel >> 24) & 0xFF;
	g = (pixel >> 16) & 0xFF;
	b = (pixel >> 8) & 0xFF;
	a = pixel & 0xFF;
	shade = 1.0 - (dist * 0.03 / 500.0);
	shade = clamp(shade, 0.0, 1.0);
	if (hit_vertical)
		shade *= 0.9;
	r = (uint8_t)(r * shade);
	g = (uint8_t)(g * shade);
	b = (uint8_t)(b * shade);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
