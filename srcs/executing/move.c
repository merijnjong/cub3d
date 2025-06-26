/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:12:31 by mjong             #+#    #+#             */
/*   Updated: 2025/06/26 16:28:42 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	refresh_frame(t_game *game)
{
	clear_image(game->gamefield);
	draw_gamefield(game);
	game->player->instances[0].x = game->x_pos;
	game->player->instances[0].y = game->y_pos;
	return ;
}

int	coll_detection(t_game *game, int x, int y, int range)
{
	if (range == 0)
		range++;
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
	if (!coll_detection(game, temp_x_pos, temp_y_pos,
			(game->block_size / 4 - 1)))
	{
		game->x_pos = temp_x_pos;
		game->y_pos = temp_y_pos;
		game->should_refresh = true;
	}
	return ;
}

void	change_direction(t_game *game, bool left)
{
	if (left == true)
	{
		game->dir -= TURN_SPEED;
		if (game->dir < 0)
			game->dir += 360;
		game->should_refresh = true;
	}
	else
	{
		game->dir += TURN_SPEED;
		if (game->dir >= 360)
			game->dir -= 360;
		game->should_refresh = true;
	}
}

void	handle_input(void *param)
{
	t_game	*game;
	double	angle_rad;

	game = (t_game *)param;
	game->should_refresh = false;
	angle_rad = game->dir * (M_PI / 180.0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		exit_game((t_game *)game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		change_direction(game, true);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		change_direction(game, false);
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
