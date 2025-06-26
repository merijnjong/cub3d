/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:56:19 by merijnjong        #+#    #+#             */
/*   Updated: 2025/06/26 16:52:58 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	exit_free(char **lines, char *content, const char *msg)
{
	if (lines)
		free_split(lines);
	if (content)
		free(content);
	exit(ft_printf("%s", msg));
}

char	**dup_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	assign_maps(t_game *game, char **split_tmp)
{
	game->map_height = count_lines(split_tmp);
	game->two_d_map = dup_map(split_tmp, game->map_height);
	game->two_d_map_check = dup_map(split_tmp, game->map_height);
}

int	validate_map_chars(t_game *game)
{
	char	c;
	int		y;
	int		x;

	y = 0;
	while (game->two_d_map[y])
	{
		x = 0;
		while (game->two_d_map[y][x])
		{
			c = game->two_d_map[y][x];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
				&& c != 'W' && c != ' ')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
