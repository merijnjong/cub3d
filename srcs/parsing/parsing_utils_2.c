/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merijnjong <merijnjong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:56:19 by merijnjong        #+#    #+#             */
/*   Updated: 2025/06/11 01:30:05 by merijnjong       ###   ########.fr       */
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
