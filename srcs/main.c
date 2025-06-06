/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merijnjong <merijnjong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
/*   Updated: 2025/06/06 15:09:28 by merijnjong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	init(t_game *game)
{
	game->x_pos = 0;
	game->y_pos = 0;
	game->dir = 270;
	game->map_width = 0;
	game->map_height = 0;
	game->tex_col_check = 0;
	game->invalid_map = 0;
	game->two_d_map = NULL;
	game->two_d_map_check = NULL;
	game->floor_colour = 0;
	game->ceiling_colour = 0;
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", false);
	if (!game->mlx)
	{
		ft_printf("Failed to initialize graphics library\n");
		exit(EXIT_FAILURE);
	}
	game->north = NULL;
	game->south = NULL;
	game->east = NULL;
	game->west = NULL;
	make_image(game);
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
	while (game.two_d_map[game.map_height])
    	game.map_height++;
	print_dbl_ptr(game.two_d_map);

	printf("kaas is anders\n");
	draw_background(&game, 0x87CEEBFF, 0x777777FF);
	printf(" als je een pet op hebt.\n");
	draw_map(&game, 0, 0);
	printf("Maar dat betekent niet...\n");
	draw_player(&game, game.x_pos, game.y_pos, 0x00FFFFFF);

	if (game.mlx)
	{
		mlx_key_hook(game.mlx, (void *)&ft_hooks, &game);
		mlx_loop(game.mlx);
	}
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
