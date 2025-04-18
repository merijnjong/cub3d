/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:21:28 by mjong             #+#    #+#             */
/*   Updated: 2025/04/18 17:16:26 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	load_texture(mlx_t *mlx, mlx_image_t **image_slot, char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_printf("Error: failed to load texture from %s\n", path);
		exit(1);
	}
	*image_slot = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!*image_slot)
	{
		ft_printf("Error: failed to convert texture to image from %s\n", path);
		exit(1);
	}
}

void	find_texture(t_game *game, char **split, char *id,
	char *path_trimmed)
{
	printf("id: %s\n", id);
	if (ft_strncmp(id, "NO", 3) == 0)
		load_texture(game->mlx, &game->north, path_trimmed);
	else if (ft_strncmp(id, "SO", 3) == 0)
		load_texture(game->mlx, &game->south, path_trimmed);
	else if (ft_strncmp(id, "WE", 3) == 0)
		load_texture(game->mlx, &game->west, path_trimmed);
	else if (ft_strncmp(id, "EA", 3) == 0)
		load_texture(game->mlx, &game->east, path_trimmed);
	else
	{
		ft_printf("Error: unknown texture identifier: %s\n", id);
		free_split(split);
		free(path_trimmed);
		exit(1);
	}
}

void	assign_texture(t_game *game, char *line)
{
	char	**split;
	char	*id;
	char	*path_trimmed;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
	{
		ft_printf("Error: invalid texture line\n");
		free_split(split);
		exit(1);
	}
	id = split[0];
	path_trimmed = ft_strtrim(split[1], "\n");
	if (!path_trimmed)
	{
		ft_printf("Error: failed to trim path\n");
		free_split(split);
		exit(1);
	}
	find_texture(game, split, id, path_trimmed);
	free(path_trimmed);
	free_split(split);
}