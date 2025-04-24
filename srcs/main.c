/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
/*   Updated: 2025/04/24 18:07:44 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	init(t_game *game)
{
	game->x_pos = 0;
	game->y_pos = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->tex_col_check = 0;
	game->invalid_map = 0;
	game->two_d_map = NULL;
	game->two_d_map_check = NULL;
	game->mlx = mlx_init(1920, 1080, "cub3d", true);
	game->north = NULL;
	game->south = NULL;
	game->east = NULL;
	game->west = NULL;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!argv[1] || argc > 2 || cub_check(argv[1]))
	{
		ft_printf(INPUT_ERROR);
		exit(1);
	}
	init(&game);
	parse_cub_file(&game, argv[1]);
	mlx_key_hook(game.mlx, (void *)&ft_hooks, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
