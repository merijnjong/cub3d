/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:18:31 by dkros             #+#    #+#             */
/*   Updated: 2025/06/25 17:32:48 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

t_col_info	build_col_info(t_game *game, double perp, const t_ray_hit *hit,
								double angle_rad)
{
	t_col_info	info;
	double		offset;

	offset = 0.0;
	info.wall_h = (int)((game->block_size * SCREEN_HEIGHT) / perp);
	if (hit->vertical == true)
		offset = fmod(hit->y, game->block_size);
	else
		offset = fmod(hit->x, game->block_size);
	info.tex_x = (int)(offset / game->block_size * game->west->width);
	info.dir_x = cos(angle_rad);
	info.dir_y = sin(angle_rad);
	return (info);
}

void	trace_column(t_game *game, int x, double ray_angle)
{
	t_ray_input	in;
	t_ray_hit	hit;
	t_col_info	cinfo;
	t_line_info	linfo;
	double		perp;

	in.start_x = game->x_pos;
	in.start_y = game->y_pos;
	in.angle_deg = ray_angle;
	in.max_distance = 1000;
	perp = cast_ray(game, in, &hit);
	if (perp <= 0.0)
		return ;
	cinfo = build_col_info(game, perp, &hit, (ray_angle * (M_PI / 180.0)));
	linfo.wall_h = cinfo.wall_h;
	linfo.screen_x = x;
	linfo.tex_x = cinfo.tex_x;
	linfo.hit_vertical = hit.vertical;
	linfo.dir_x = cos((ray_angle * (M_PI / 180.0)));
	linfo.dir_y = sin((ray_angle * (M_PI / 180.0)));
	draw_game_line(game, &linfo);
}

void	draw_background_2(mlx_image_t *img, int color, int i)
{
	int	j;

	j = 0;
	if (!img)
		return ;
	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			my_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}
