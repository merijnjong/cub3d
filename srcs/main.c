/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/26 16:09:11 by mjong            ###   ########.fr       */
=======
/*   Updated: 2025/06/26 16:25:51 by dkros            ###   ########.fr       */
>>>>>>> ab1caa016fe44bfc7a6630f40b3295c9d7e738b5
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	get_block_size(t_game *game)
{
	if (game->map_height >= game->map_width)
		return (game->block_size = (SCREEN_HEIGHT / game->map_height) / 2);
	else
		return (game->block_size = (SCREEN_WIDTH / game->map_width) / 2);
}

void	initialise(t_game *game)
{
	game->x_pos = 0;
	game->y_pos = 0;
	game->dir = 270;
	game->invalid_map = 0;
	game->tex_col_check = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->block_size = 20;
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

void	put_images_to_window(t_game *game)
{
	mlx_image_to_window(game->mlx, game->background, 0, 0);
	mlx_image_to_window(game->mlx, game->gamefield, 0, 0);
	mlx_image_to_window(game->mlx, game->map, 0, 0);
	mlx_image_to_window(game->mlx, game->player, game->x_pos, game->y_pos);
	return ;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!argv[1] || argc > 2 || cub_check(argv[1]))
		return (ft_printf(INPUT_ERROR), 1);
	initialise(&game);
	parse_cub_file(&game, argv[1]);
	while (game.two_d_map[game.map_height])
		game.map_height++;
	draw_background(&game, game.ceiling_colour, game.floor_colour);
	game.gamefield = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	draw_gamefield(&game);
	draw_map(&game, 0, 0);
	draw_player(&game, game.x_pos, game.y_pos);
	put_images_to_window(&game);
	if (game.mlx)
	{
		mlx_loop_hook(game.mlx, handle_input, &game);
		mlx_close_hook(game.mlx, exit_game, &game);
		mlx_loop(game.mlx);
	}
	free_split(game.two_d_map);
	mlx_terminate(game.mlx);
	return (0);
}
