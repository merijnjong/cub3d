/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:12:31 by mjong             #+#    #+#             */
/*   Updated: 2025/06/10 16:33:00 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void exit_game(t_game *game)
{
	mlx_terminate(game->mlx);
	ft_free(game->two_d_map);
	exit(EXIT_SUCCESS);
}

void move_forward(t_game *game, double angle_rad)
{
	int	temp_x_pos;
	int	temp_y_pos;

	temp_x_pos = (cos(angle_rad) * 5) + game->x_pos;
	temp_y_pos = (sin(angle_rad) * 5) + game->y_pos;
	
	if (!is_wall(game, temp_x_pos + 1, temp_y_pos + 1))
	{
		game->x_pos = temp_x_pos;
		game->y_pos = temp_y_pos;
	}
	return ;
}

void move_backwards(t_game *game, double angle_rad)
{
	int	temp_x_pos;
	int	temp_y_pos;

	temp_x_pos = game->x_pos - (cos(angle_rad) * 5);
	temp_y_pos = game->y_pos - (sin(angle_rad) * 5);
	
	if (!is_wall(game, temp_x_pos - 1, temp_y_pos - 1))
	{
		game->x_pos = temp_x_pos;
		game->y_pos = temp_y_pos;
	}
	return ;
}

void move_left(t_game *game, double angle_rad)
{
	int	temp_x_pos;
	int	temp_y_pos;

	temp_x_pos = (cos(angle_rad + M_PI * 1.5) * 5) + game->x_pos;
	temp_y_pos = (sin(angle_rad + M_PI * 1.5) * 5) + game->y_pos;
	
	if (!is_wall(game, temp_x_pos + 1, temp_y_pos + 1))
	{
		game->x_pos = temp_x_pos;
		game->y_pos = temp_y_pos;
	}
	return ;
}

void move_right(t_game *game, double angle_rad)
{
	int	temp_x_pos;
	int	temp_y_pos;

	temp_x_pos = game->x_pos - (cos(angle_rad + M_PI * 1.5) * 5);
	temp_y_pos = game->y_pos - (sin(angle_rad + M_PI * 1.5) * 5);
	
	if (!is_wall(game, temp_x_pos - 1, temp_y_pos - 1))
	{
		game->x_pos = temp_x_pos;
		game->y_pos = temp_y_pos;
	}
	return ;
}

void	ft_hooks(mlx_key_data_t keydata, t_game *game)
{
	double angle_rad;

	angle_rad = game->dir * (M_PI / 180.0);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			exit_game(game);
		if (keydata.key == MLX_KEY_LEFT)
			game->dir = fmod(game->dir - 5, 360);
		if (keydata.key == MLX_KEY_RIGHT)
			game->dir = fmod(game->dir + 5, 360);
		if (keydata.key == MLX_KEY_W)
			move_forward(game, angle_rad);
		if (keydata.key == MLX_KEY_A)
			move_left(game, angle_rad);
		if (keydata.key == MLX_KEY_S)
			move_backwards(game, angle_rad);
		if (keydata.key == MLX_KEY_D)
			move_right(game, angle_rad);

		mlx_delete_image(game->mlx, game->player);
		mlx_delete_image(game->mlx, game->gamefield);
		draw_gamefield(game);
		mlx_image_to_window(game->mlx, game->map, 0, 0);
		draw_player(game, game->x_pos, game->y_pos);
	}
}
