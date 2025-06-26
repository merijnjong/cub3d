/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:21:28 by mjong             #+#    #+#             */
/*   Updated: 2025/06/26 16:55:46 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	load_texture(mlx_t *mlx, mlx_image_t **image_slot, char *path)
{
	mlx_texture_t	*texture;

	if (access(path, R_OK) != 0)
	{
		ft_printf("Error: cannot access texture file: %s\n", path);
		exit(1);
	}
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

int	validate_texture_line_format(char **split, char *line)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	if (count != 2)
	{
		ft_printf("\033[1;31mError: invalid texture line format:\
 \"%s\"\n\033[0m", line);
		return (0);
	}
	return (1);
}

void	assign_texture(t_game *game, char *line)
{
	char	**split;
	char	*id;
	char	*path_trimmed;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
	{
		free_split(split);
		exit(ft_printf(TEX_ERROR));
	}
	if (!validate_texture_line_format(split, line))
	{
		free_split(split);
		exit(1);
	}
	id = split[0];
	path_trimmed = ft_strtrim(split[1], "\n");
	if (!path_trimmed)
	{
		free_split(split);
		exit(ft_printf("Error: failed to trim path\n"));
	}
	find_texture(game, split, id, path_trimmed);
	free(path_trimmed);
	free_split(split);
}

void	check_texture_line(t_game *game, char *line, t_tex_col *tex)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (tex->no++)
			exit(ft_printf(TEX_ERROR));
		assign_texture(game, line);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (tex->so++)
			exit(ft_printf(TEX_ERROR));
		assign_texture(game, line);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (tex->we++)
			exit(ft_printf(TEX_ERROR));
		assign_texture(game, line);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (tex->ea++)
			exit(ft_printf(TEX_ERROR));
		assign_texture(game, line);
	}
	game->tex_col_check++;
}
