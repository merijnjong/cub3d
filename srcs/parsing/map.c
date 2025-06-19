/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:29 by mjong             #+#    #+#             */
/*   Updated: 2025/06/18 17:52:55 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	has_excess_trailing_walls(char **map)
{
	int	i = 0;
	int	standalone_1_count = 0;
	int	found_main_map = 0;

	while (map[i])
	{
		char	*line = map[i];

		int	j = 0;
		int	has_other_than_wall = 0;

		while (line[j])
		{
			if (line[j] == '0' || line[j] == 'N' || line[j] == 'S' ||
				line[j] == 'E' || line[j] == 'W')
			{
				has_other_than_wall = 1;
				break ;
			}
			j++;
		}
		if (has_other_than_wall)
			found_main_map = 1;
		else if (found_main_map)
		{
			j = 0;
			while (line[j])
			{
				if (line[j] != '1' && line[j] != ' ' && line[j] != '\t')
					return (1);
				j++;
			}
			standalone_1_count++;
			if (standalone_1_count > 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	has_horizontal_spike(char **map)
{
	int	i = 0;
	int	total_len = 0;
	int	line_count = 0;
	int	len;

	while (map[i])
	{
		len = ft_strlen(map[i]);
		total_len += len;
		line_count++;
		i++;
	}
	if (line_count == 0)
		return (0);
	int	avg_len = total_len / line_count;
	int	max_allowed = avg_len + 3;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max_allowed)
			return (1);
		i++;
	}
	return (0);
}

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
	if (game->invalid_map == 1 || has_excess_trailing_walls(game->two_d_map) || has_horizontal_spike(game->two_d_map))
	{
		ft_printf(FLOOD_FILL_ERROR);
		exit(1);
	}
}
