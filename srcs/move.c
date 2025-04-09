/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:12:31 by mjong             #+#    #+#             */
/*   Updated: 2025/04/09 16:26:49 by mjong            ###   ########.fr       */
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
	uint32_t	pov_dir;

	x_dir = 0;
	y_dir = 0;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			exit(EXIT_SUCCESS); //needs a seperate function
		if (keydata.key == MLX_KEY_W)
			y_dir = -100;
		if (keydata.key == MLX_KEY_A)
			x_dir = -100;
		if (keydata.key == MLX_KEY_S)
			y_dir = 100;
		if (keydata.key == MLX_KEY_D)
			x_dir = 100;
		if (keydata.key == MLX_KEY_LEFT)
			pov_dir = -10;
		if (keydata.key == MLX_KEY_RIGHT)
			pov_dir = 10;
		if (x_dir || y_dir || pov_dir)
			move_player(game, x_dir, y_dir, pov_dir);
	}
}
