/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
/*   Updated: 2025/04/09 16:40:57 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

char	*file_to_map(char *filename)
{
	char	*temp;
	char	*map;
	int		fd;

	map = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nINVALID MAP\n");
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
	return (map);
}

void	init(t_game *game)
{
	game->x_pos = 0;
	game->y_pos = 0;
	game->map_width = 0;
	game->map_height = 0;
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
	char	*map;

	if (!argv[1] || argc > 2)
	{
		ft_printf("Error, wrong input\n");
		ft_printf("Correct input: ./cub3d maps/map.ber\n");
		exit(1);
	}
	init(&game);
	map = file_to_map(argv[1]);
	mlx_key_hook(game.mlx, (void *)&ft_hooks, &game);
	return (0);
}
