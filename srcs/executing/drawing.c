/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:40:18 by dkros             #+#    #+#             */
/*   Updated: 2025/06/25 15:15:07 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	draw_gamefield(t_game *game)
{
	int		x;
	double	fov_half;
	double	d_angle;
	double	ray_angle;
	double	start_ang;

	x = 0;
	fov_half = 30.0;
	d_angle = 60.0 / (double)SCREEN_WIDTH;
	start_ang = game->dir - fov_half;
	while (x < SCREEN_WIDTH)
	{
		ray_angle = fmod(start_ang + x * d_angle + 360.0, 360.0);
		trace_column(game, x, ray_angle);
		x++;
	}
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
	draw_background_2(game->background, color_2, i);
}

void	draw_map(t_game *game, int i, int j)
{
	game->map = mlx_new_image(game->mlx, game->map_width * game->block_size,
			game->map_height * game->block_size);
	while (game->two_d_map && game->two_d_map[i])
	{
		j = 0;
		while (game->two_d_map[i][j])
		{
			if (game->two_d_map[i][j] == '1')
				draw_square(game, (j * game->block_size),
					(i * game->block_size), 0x000000FF);
			else if (game->two_d_map[i][j] == ' ')
				draw_square(game, (j * game->block_size),
					(i * game->block_size), 0x00000000);
			else if (is_alpha(game->two_d_map[i][j]))
				draw_square(game, (j * game->block_size),
					(i * game->block_size), 0XFFFFFFFF);
			else
				draw_square(game, (j * game->block_size),
					(i * game->block_size), 0XFFFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game, int x, int y)
{
	int	i;
	int	j;

	(void)(x);
	(void)(y);
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
}
