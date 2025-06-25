/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:18 by dkros             #+#    #+#             */
/*   Updated: 2025/06/25 17:20:23 by dkros            ###   ########.fr       */
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

double	cast_ray(t_game *game, t_ray_input in, t_ray_hit *hit)
{
	t_ray	ray;
	double	dist;
	double	ang_rad;

	ang_rad = deg_to_rad(in.angle_deg);
	ray.dir_x = cos(ang_rad);
	ray.dir_y = sin(ang_rad);
	init_ray(&ray, game, in.start_x, in.start_y);
	init_step(&ray, game, in.start_x, in.start_y);
	perform_dda(&ray, game);
	dist = perp_distance(&ray);
	if (dist > (double)in.max_distance)
		return (-1.0);
	if (hit)
	{
		hit->vertical = ray.side;
		hit->x = in.start_x + ray.dir_x * dist;
		hit->y = in.start_y + ray.dir_y * dist;
	}
	return (dist);
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
