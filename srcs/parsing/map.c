/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:29 by mjong             #+#    #+#             */
/*   Updated: 2025/07/31 13:20:32 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	has_horizontal_spike(t_game *game)
{
	int	row_lengths[256];
	int	row_cnt;
	int	avg_len;
	int	limit;
	int	spike;

	get_row_lengths(game, row_lengths, &row_cnt);
	if (row_cnt == 0)
		return (0);
	avg_len = average_int(row_lengths, row_cnt);
	limit = avg_len + SPIKE_MARGIN;
	spike = has_value_above(row_lengths, row_cnt, limit);
	if (spike == 1)
		game->invalid_map = 1;
	return (spike);
}

int	has_vertical_spike(t_game *game)
{
	int	*heights;
	int	avg;
	int	limit;
	int	spike;

	heights = ft_calloc(game->map_width, sizeof(int));
	if (!heights)
		return (1);
	count_column_heights(game, heights);
	avg = average_int(heights, game->map_width);
	limit = avg + SPIKE_MARGIN;
	spike = has_value_above(heights, game->map_width, limit);
	free(heights);
	return (spike);
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

void	count_map_dimensions(t_game *game, t_tex_col *tex_col)
{
	int			curr_len;
	int			x;
	int			y;

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
	game->block_size = get_block_size(game);
	pad_map_lines(game->two_d_map_check, game->map_width);
	find_and_validate_player(game, tex_col);
	flood_fill(game,
		game->x_pos / game->block_size, game->y_pos / game->block_size);
	if (validate_map_chars(game, tex_col) || game->invalid_map == 1
		|| has_vertical_spike(game) || has_horizontal_spike(game))
		exit_and_print(1, FLOOD_FILL_ERROR);
}
