/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:22:43 by mjong             #+#    #+#             */
/*   Updated: 2025/04/18 14:33:58 by dkros            ###   ########.fr       */
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
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", false);
	game->roof = NULL;
	game->floor = NULL;
	game->north = NULL;
	game->east = NULL;
	game->south = NULL;
	game->west = NULL;
}

// void	prep_draw_line(t_game *data)
// {
// 	int	dx;
// 	int	sx;
// 	int	sy;

// 	dx = abs(data->c.x2 - data->c.x1);
// 	data->c.dy = abs(data->c.y2 - data->c.y1);
// 	if (data->c.x1 < data->c.x2)
// 		sx = 1;
// 	else
// 		sx = -1;
// 	if (data->c.y1 < data->c.y2)
// 		sy = 1;
// 	else
// 		sy = -1;
// 	draw_line(data, dx, sx, sy);
// 	return ;
// }

void	my_pixel_put(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && x < (int)img->height && y >= 0 && y < (int)img->width)
	{
		mlx_put_pixel(img, x, y, color);
	}
	return;
}

// void	draw_line(t_game *data, int dx, int sx, int sy)
// {
// 	int	e2;
// 	int	err;

// 	if (dx > data->c.dy)
// 		err = dx / 2;
// 	else
// 		err = -(data->c.dy) / 2;
// 	while (1)
// 	{
// 		my_pixel_put(data, (data->c.x1 + 100), (data->c.y1 + 75), 0xFFFFFFFF);
// 		if (data->c.x1 == data->c.x2 && data->c.y1 == data->c.y2)
// 			break ;
// 		e2 = err;
// 		if (e2 > -dx)
// 		{
// 			err -= data->c.dy;
// 			data->c.x1 += sx;
// 		}
// 		if (e2 < data->c.dy)
// 		{
// 			err += dx;
// 			data->c.y1 += sy;
// 		}
// 	}
// 	return ;
// }

mlx_image_t *draw_square(t_game *data, int x, int y, int size, int color)
{
	int i;
	int j;


	(void)color;
	data->img = mlx_new_image(data->mlx, size, size);
	if (!data->img)
	return (NULL);
	i = 0;
	while (i < (size - 1))
	{
		j = 0;
		while (j < (size - 1))
		{
			my_pixel_put(data->img, j, i, color);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx, data->img, x, y);
	return (data->img);
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
	print_dbl_ptr(game.two_d_map);
	init(&game);

	int i;
	// int j;

	i = 0;

	// while (i < 5)
	// {
	// 	j = 0;
	// 	while (j < 5)
	// 	{
	// 		if (test[(i * 5) + j] && test[(i * 5) + j] == 1)
	// 			draw_square(&game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0x000000FF);
	// 		else if (test[(i * 5) + j] && test[(i * 5) + j] == 2)
	// 			draw_square(&game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0XFF0000FF);
	// 		else
	// 			draw_square(&game, (j * BLOCK_SIZE), (i * BLOCK_SIZE), BLOCK_SIZE, 0XFFFFFFFF);
	// 		j++;
	// 	}
	// 	i++;
	// }

	if (game.mlx)
	{
		mlx_key_hook(game.mlx, (void *)&ft_hooks, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
