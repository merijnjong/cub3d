/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:40:51 by dkros             #+#    #+#             */
/*   Updated: 2025/06/25 14:55:26 by dkros            ###   ########.fr       */
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

void	init_ray(t_ray *r, t_game *g, int sx, int sy)
{
	r->map_x = sx / g->block_size;
	r->map_y = sy / g->block_size;
	r->delta_x = fabs(1.0 / r->dir_x) * g->block_size;
	r->delta_y = fabs(1.0 / r->dir_y) * g->block_size;
}

void	init_step(t_ray *r, t_game *g, int sx, int sy)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = ((sx / (double)g->block_size) - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0
				- (sx / (double)g->block_size)) * r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = ((sy / (double)g->block_size) - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0
				- (sy / (double)g->block_size)) * r->delta_y;
	}
}

void	perform_dda(t_ray *r, t_game *g)
{
	while (in_bounds(g, r->map_x, r->map_y)
		&& g->two_d_map[r->map_y][r->map_x] != '1')
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = true;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = false;
		}
	}
}

double	perp_distance(t_ray *r)
{
	if (r->side)
		return (r->side_x - r->delta_x);
	return (r->side_y - r->delta_y);
}
