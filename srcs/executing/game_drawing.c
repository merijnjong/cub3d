/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:11:45 by dkros             #+#    #+#             */
/*   Updated: 2025/06/25 15:31:28 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

mlx_image_t	*choose_texture(t_game *g, bool vert,
									double dx, double dy)
{
	mlx_image_t	*tex;

	tex = NULL;
	if (vert == true)
	{
		if (dx > 0)
			tex = g->west;
		else
			tex = g->east;
	}
	else
	{
		if (dy > 0)
			tex = g->south;
		else
			tex = g->north;
	}
	return (tex);
}

void	get_column_bounds(int wall_h, int *top, int *bottom)
{
	int	mid;
	int	half_h;

	mid = SCREEN_HEIGHT / 2;
	half_h = wall_h / 2;
	*top = mid - half_h;
	*bottom = mid + half_h;
}

uint32_t	sample_tex_color(mlx_image_t *tex, int x, int y)
{
	int			byte_off;
	uint8_t		*p;
	uint32_t	pixel;

	byte_off = (y * tex->width + x) * 4;
	p = (uint8_t *)tex->pixels;
	pixel = ((uint32_t)p[byte_off] << 24)
		| ((uint32_t)p[byte_off + 1] << 16)
		| ((uint32_t)p[byte_off + 2] << 8)
		| ((uint32_t)p[byte_off + 3]);
	return (pixel);
}

void	draw_game_line(t_game *g, t_line_info *c)
{
	mlx_image_t	*tex;
	int			top;
	int			bottom;
	int			y;

	tex = choose_texture(g, c->hit_vertical, c->dir_x, c->dir_y);
	if (tex == NULL)
		return ;
	get_column_bounds(c->wall_h, &top, &bottom);
	y = top;
	while (y < bottom)
	{
		if (y >= 0 && y <= SCREEN_HEIGHT)
		{
			my_pixel_put(g->gamefield, c->screen_x, y,
				get_shaded_color(
					sample_tex_color(tex, c->tex_x,
						(y - top) * tex->height / c->wall_h),
					c->wall_h, c->hit_vertical));
		}
		y++;
	}
}
