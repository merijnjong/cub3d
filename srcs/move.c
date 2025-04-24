/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:12:31 by mjong             #+#    #+#             */
/*   Updated: 2025/04/24 18:01:42 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	move_player(t_game *game, uint32_t x_dir, uint32_t y_dir,
		uint32_t pov_dir)
{
	game = NULL;
	x_dir = 0;
	y_dir = 0;
	pov_dir = 0;
}

void	ft_hooks(mlx_key_data_t keydata, t_game *game)
{
	uint32_t	x_dir;
	uint32_t	y_dir;
	// uint32_t	pov_dir;

	x_dir = 0;
	y_dir = 0;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			exit(EXIT_SUCCESS); //needs a seperate function
		if (keydata.key == MLX_KEY_LEFT)
			game->dir -= 5;
		if (keydata.key == MLX_KEY_RIGHT)
			game->dir += 5;
		if (keydata.key == MLX_KEY_W)
			game->y_pos -= 10;
		if (keydata.key == MLX_KEY_A)
			game->x_pos -= 10;
		if (keydata.key == MLX_KEY_S)
			game->y_pos += 10;
		if (keydata.key == MLX_KEY_D)
			game->x_pos += 10;
		mlx_delete_image(game->mlx, game->player);
		draw_player(game, game->x_pos, game->y_pos, 0x00FFFFFF);
		// if (x_dir || y_dir || pov_dir)
		// 	move_player(game, x_dir, y_dir, pov_dir);
	}
}
