/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:29 by mjong             #+#    #+#             */
/*   Updated: 2025/04/16 18:09:43 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	flood_fill(t_game *game, int x, int y)
{
	char	c;

	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
	{
		game->invalid_map = 1;
		return ;
	}
	c = game->two_d_map_check[y][x];
	if (c == '1' || c == 'F' || c == ' ')
		return ;
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

void	count_map_dimensions(t_game *game)
{
	int	y;
	int	x;
	int	curr_len;

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
	flood_fill(game, 1, 1);
	if (game->invalid_map == 1)
	{
		ft_printf(FLOOD_FILL_ERROR);
		exit(1);
	}
}

int	cub_check(char *line)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(line);
	if (len < 4)
		return (1);
	i = len - 4;
	if (line[i] != '.' || line[i + 1] != 'c'
		|| line[i + 2] != 'u' || line[i + 3] != 'b')
		return (1);
	return (0);
}
