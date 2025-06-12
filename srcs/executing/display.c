/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:51:52 by mjong             #+#    #+#             */
/*   Updated: 2025/06/12 13:34:05 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	make_image(t_game *game)
{
	mlx_texture_t	*n;
	mlx_texture_t	*e;
	mlx_texture_t	*s;
	mlx_texture_t	*w;

	n = mlx_load_png("textures/stone2.png");
	e = mlx_load_png("textures/grass2.png");
	s = mlx_load_png("textures/south.png");
	w = mlx_load_png("textures/west.png");
	game->north = mlx_texture_to_image(game->mlx, n);
	game->east = mlx_texture_to_image(game->mlx, e);
	game->south = mlx_texture_to_image(game->mlx, s);
	game->west = mlx_texture_to_image(game->mlx, w);
}
