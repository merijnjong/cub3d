/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
/*   Updated: 2025/04/16 15:21:11 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	file_to_map(t_game *game, char *filename)
{
	char	*temp;
	char	*map;
	int		fd;

	map = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(MAP_ERROR);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		map = ft_strjoin2(map, temp);
		free(temp);
	}
	close(fd);
	game->two_d_map = ft_split(map, '\n');
}

void	init(t_game *game)
{
	game->x_pos = 0;
	game->y_pos = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->two_d_map = NULL;
	game->mlx = mlx_init(1920, 1080, "cub3d", true);
	game->roof = NULL;
	game->floor = NULL;
	game->north = NULL;
	game->east = NULL;
	game->south = NULL;
	game->west = NULL;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!argv[1] || argc > 2)
	{
		ft_printf(INPUT_ERROR);
		exit(1);
	}
	file_to_map(&game, argv[1]);
	init(&game);
	mlx_key_hook(game.mlx, (void *)&ft_hooks, &game);
	return (0);
}
