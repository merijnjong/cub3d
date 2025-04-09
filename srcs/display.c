/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:51:52 by mjong             #+#    #+#             */
/*   Updated: 2025/04/09 16:02:52 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	make_image(t_game *game)
{
	mlx_texture_t	*r;
	mlx_texture_t	*f;
	mlx_texture_t	*n;
	mlx_texture_t	*e;
	mlx_texture_t	*s;
	mlx_texture_t	*w;

	r = mlx_load_png("./textures/roof.png");
	f = mlx_load_png("./textures/floor.png");
	n = mlx_load_png("./textures/north.png");
	e = mlx_load_png("./textures/east.png");
	s = mlx_load_png("./textures/south.png");
	w = mlx_load_png("./textures/west.png");
	game->roof = mlx_texture_to_image(game->mlx, r);
	game->floor = mlx_texture_to_image(game->mlx, f);
	game->north = mlx_texture_to_image(game->mlx, n);
	game->east = mlx_texture_to_image(game->mlx, e);
	game->south = mlx_texture_to_image(game->mlx, s);
	game->west = mlx_texture_to_image(game->mlx, w);
	mlx_delete_texture(r);
	mlx_delete_texture(f);
	mlx_delete_texture(n);
	mlx_delete_texture(e);
	mlx_delete_texture(s);
	mlx_delete_texture(w);
}
