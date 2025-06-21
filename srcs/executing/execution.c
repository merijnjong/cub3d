/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merijnjong <merijnjong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
/*   Updated: 2025/06/21 02:45:19 by merijnjong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

mlx_image_t	*draw_square(t_game *data, int x, int y, int size, int color)
{
	int	i;
	int	j;

	if (!data->map)
		return (NULL);
	i = 0;
	while (i < (size - 1))
	{
		j = 0;
		while (j < (size - 1))
		{
			my_pixel_put(data->map, j + x, i + y, color);
			j++;
		}
		i++;
	}
	return (data->map);
}

bool	in_bounds(t_game *g, int x, int y)
{
	if (y < 0 || y >= g->map_height)
		return (false);
	if (x < 0 || x >= (int)ft_strlen(g->two_d_map[y]))
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
		exit_game(game);
	}
	game->x_pos = i * game->block_size;
	game->y_pos = j * game->block_size;
}

void	exit_game(t_game *game)
{
	mlx_terminate(game->mlx);
	ft_free(game->two_d_map);
	exit(EXIT_SUCCESS);
}
