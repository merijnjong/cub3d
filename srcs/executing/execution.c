/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
/*   Updated: 2025/06/26 16:28:24 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

mlx_image_t	*draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	if (!game->map)
		return (NULL);
	i = 0;
	size = game->block_size;
	while (i < (size - 1))
	{
		j = 0;
		while (j < (size - 1))
		{
			my_pixel_put(game->map, j + x, i + y, color);
			j++;
		}
		i++;
	}
	return (game->map);
}

bool	in_bounds(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map_height)
		return (false);
	if (x < 0 || x >= (int)ft_strlen(game->two_d_map[y]))
		return (false);
	return (true);
}

void	set_player_position(t_game *game, char c, int i, int j)
{
	printf("%c", c);
	if (c == 'N')
		game->dir = 270;
	else if (c == 'S')
		game->dir = 90;
	else if (c == 'W')
		game->dir = 180;
	else if (c == 'E')
		game->dir = 0;
	else
	{
		printf("Invalid character found\n");
		exit_game((t_game *)game);
	}
	game->x_pos = i * game->block_size;
	game->y_pos = j * game->block_size;
}

void	exit_game(void *param)
{
	t_game	*game;

	game = param;
	mlx_terminate(game->mlx);
	ft_free(game->two_d_map);
	exit(EXIT_SUCCESS);
}
