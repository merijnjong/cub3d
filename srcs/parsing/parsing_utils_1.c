/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:30:45 by mjong             #+#    #+#             */
/*   Updated: 2025/06/12 13:21:50 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	has_internal_empty_line(char *str)
{
	int	line_empty;
	int	i;

	i = 0;
	while (str[i] == '\n')
		i++;
	while (str[i])
	{
		line_empty = 1;
		while (str[i] && str[i] != '\n')
		{
			if (str[i] != ' ' && str[i] != '\t')
				line_empty = 0;
			i++;
		}
		if (line_empty)
			return (1);
		if (str[i] == '\n' && str[i + 1] == '\n')
			return (1);
		if (str[i])
			i++;
	}
	return (0);
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

void	find_and_validate_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->two_d_map[y])
	{
		x = 0;
		while (game->two_d_map[y][x])
		{
			if (game->two_d_map[y][x] == 'N' || game->two_d_map[y][x] == 'S'
				|| game->two_d_map[y][x] == 'E' || game->two_d_map[y][x] == 'W')
			{
				if (x == 0 || x == game->map_width - 1 || y == 0
					|| y == game->map_height - 1)
					exit(ft_printf(PLAYER_ERROR));
				game->x_pos = x * BLOCK_SIZE;
				game->y_pos = y * BLOCK_SIZE;
				return ;
			}
			x++;
		}
		y++;
	}
	exit(ft_printf(PLAYER_ERROR));
}

int	count_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
