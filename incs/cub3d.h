/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:23:18 by mjong             #+#    #+#             */
/*   Updated: 2025/04/16 17:51:24 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include "MLX42/MLX42.h"
# include "../incs/libft.h"

# define INPUT_ERROR "\033[1;31mError, wrong input\
	\nCorrect input:./cub3d maps/map.cub\n\033[0m"
# define MAP_ERROR "\033[1;31mError, invalid map\
	\nCorrect map format: maps/map.cub\n\033[0m"
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define BLOCK_SIZE 50

typedef struct s_line_data_t
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	dy;
}	t_line_data;

typedef struct t_data
{
	int			x_pos;
	int			y_pos;
	int			map_width;
	int			map_height;
	char		**two_d_map;
	mlx_t		*mlx;
	mlx_image_t	*roof;
	mlx_image_t *img;
	t_line_data c;
	mlx_image_t *floor;
	mlx_image_t	*north;
	mlx_image_t	*east;
	mlx_image_t	*south;
	mlx_image_t	*west;
}	t_game;

void		ft_hooks(mlx_key_data_t keydata, t_game *game);
// void	prep_draw_line(t_game *data);
// void	draw_line(t_game *data, int dx, int sx, int sy);
mlx_image_t *draw_square(t_game *data, int x, int y, int size, int color);
void		my_pixel_put(mlx_image_t *img, int x, int y, int color);

//srcs/utils.c
void	print_dbl_ptr(char **ptr);

#endif