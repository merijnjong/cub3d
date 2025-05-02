/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:12:31 by mjong             #+#    #+#             */
/*   Updated: 2025/05/02 15:49:29 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void exit_game(t_game *game)
{
	mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}

void	ft_hooks(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			exit_game(game);
		if (keydata.key == MLX_KEY_LEFT)
			game->dir = fmod(game->dir - 5, 360);
		if (keydata.key == MLX_KEY_RIGHT)
			game->dir = fmod(game->dir + 5, 360);
		if (keydata.key == MLX_KEY_W)
			game->y_pos -= 10;
		if (keydata.key == MLX_KEY_A)
			game->x_pos -= 10;
		if (keydata.key == MLX_KEY_S)
			game->y_pos += 10;
		if (keydata.key == MLX_KEY_D)
			game->x_pos += 10;

		mlx_delete_image(game->mlx, game->player);
		mlx_delete_image(game->mlx, game->gamefield);
		draw_player(game, game->x_pos, game->y_pos, 0x00FFFFFF);
	}
}
