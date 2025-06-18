/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:12:31 by mjong             #+#    #+#             */
/*   Updated: 2025/06/18 17:58:34 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void refresh_frame(t_game *game)
{
	mlx_delete_image(game->mlx, game->gamefield);
	draw_gamefield(game);
	mlx_delete_image(game->mlx, game->player);
	mlx_image_to_window(game->mlx, game->map, 0, 0);
	draw_player(game, game->x_pos, game->y_pos);
	return ;
}

int collission_detection(t_game *game, int x, int y, int range)
{
	if (!is_wall(game, x + range, y + range)
		&& !is_wall(game, x - range, y - range)
		&& !is_wall(game, x + range, y - range)
		&& !is_wall(game, x - range, y + range))
		return (0);
	return (1);
}

void	move_player(t_game *game, double angle_rad, double angle_offset,
		int direction)
{
	double	move_angle;
	int		temp_x_pos;
	int		temp_y_pos;

	move_angle = angle_rad + angle_offset;
	if (direction == -1)
		move_angle += M_PI;
	temp_x_pos = (int)(cos(move_angle) * WALK_SPEED) + game->x_pos;
	temp_y_pos = (int)(sin(move_angle) * WALK_SPEED) + game->y_pos;
	if (!collission_detection(game, temp_x_pos, temp_y_pos, (BLOCK_SIZE / 4 - 1)))
	{
		game->x_pos = temp_x_pos;
		game->y_pos = temp_y_pos;
		game->should_refresh = true;
	}
	return;
}


void	handle_input(void *param)
{
	t_game	*game;
	double	angle_rad;
	game = (t_game *)param;
	game->should_refresh = false;

	angle_rad = game->dir * (M_PI / 180.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		exit_game(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->dir -= TURN_SPEED;
		if (game->dir < 0)
			game->dir += 360;
		game->should_refresh = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->dir += TURN_SPEED;
		if (game->dir >= 360)
			game->dir -= 360;
		game->should_refresh = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, angle_rad, 0, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, angle_rad, 0, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player(game, angle_rad, M_PI / 2, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game, angle_rad, M_PI / 2, 1);
	
	if (game->should_refresh)
		refresh_frame(game);
}
