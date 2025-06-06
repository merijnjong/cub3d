/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merijnjong <merijnjong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:56:19 by merijnjong        #+#    #+#             */
/*   Updated: 2025/06/06 17:57:01 by merijnjong       ###   ########.fr       */
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

void	assign_maps(t_game *game, char **split_tmp)
{
	game->map_height = count_lines(split_tmp);
	game->two_d_map = dup_map(split_tmp, game->map_height);
	game->two_d_map_check = dup_map(split_tmp, game->map_height);
}
