/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:40:51 by dkros             #+#    #+#             */
/*   Updated: 2025/06/25 17:17:15 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

double	deg_to_rad(double deg)
{
	double	rad;

	rad = fmod(deg * (M_PI / 180.0), 2 * M_PI);
	if (rad < 0)
		rad += 2 * M_PI;
	return (rad);
}

void	init_ray(t_ray *ray, t_game *game, int sx, int sy)
{
	ray->map_x = sx / game->block_size;
	ray->map_y = sy / game->block_size;
	ray->delta_x = fabs(1.0 / ray->dir_x) * game->block_size;
	ray->delta_y = fabs(1.0 / ray->dir_y) * game->block_size;
}

void	init_step(t_ray *ray, t_game *game, int sx, int sy)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = ((sx / (double)game->block_size) - ray->map_x)
			* ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0
				- (sx / (double)game->block_size)) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = ((sy / (double)game->block_size) - ray->map_y)
			* ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0
				- (sy / (double)game->block_size)) * ray->delta_y;
	}
}

void	perform_dda(t_ray *ray, t_game *game)
{
	while (in_bounds(game, ray->map_x, ray->map_y)
		&& game->two_d_map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = true;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = false;
		}
	}
}

double	perp_distance(t_ray *ray)
{
	if (ray->side)
		return (ray->side_x - ray->delta_x);
	return (ray->side_y - ray->delta_y);
}
