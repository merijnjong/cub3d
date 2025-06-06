/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:29 by mjong             #+#    #+#             */
/*   Updated: 2025/06/06 17:18:59 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	flood_fill(t_game *game, int x, int y)
{
	char	c;

	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
	{
		game->invalid_map = 1;
		return ;
	}
	c = game->two_d_map_check[y][x];
	if (c == '1' || c == 'F')
		return ;
	if (c == 'P' || c == ' ')
	{
		game->invalid_map = 1;
		return ;
	}
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
	{
		game->invalid_map = 1;
		return ;
	}
	game->two_d_map_check[y][x] = 'F';
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}

void	pad_map_lines(char **map, int width)
{
	char	*padded;
	int		len;
	int		i;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len < width)
		{
			padded = malloc(width + 1);
			if (!padded)
			{
				ft_printf("Malloc failed in pad_map_lines\n");
				exit(1);
			}
			ft_memcpy(padded, map[i], len);
			ft_memset(padded + len, 'P', width - len);
			padded[width] = '\0';
			free(map[i]);
			map[i] = padded;
		}
		i++;
	}
}

void	count_map_dimensions(t_game *game)
{
	int	curr_len;
	int	x;
	int	y;

	y = 0;
	game->map_width = 0;
	while (game->two_d_map[y] != 0)
	{
		x = 0;
		while (game->two_d_map[y][x] != 0)
			x++;
		curr_len = x;
		if (curr_len > game->map_width)
			game->map_width = curr_len;
		y++;
	}
	game->map_height = y;
	pad_map_lines(game->two_d_map_check, game->map_width);
	find_and_validate_player(game);
	flood_fill(game, game->x_pos / BLOCK_SIZE, game->y_pos / BLOCK_SIZE);
	if (game->invalid_map == 1)
	{
		ft_printf(FLOOD_FILL_ERROR);
		exit(1);
	}
}
