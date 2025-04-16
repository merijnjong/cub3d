/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:23:18 by mjong             #+#    #+#             */
/*   Updated: 2025/04/16 15:23:53 by mjong            ###   ########.fr       */
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

typedef struct t_data
{
	int			x_pos;
	int			y_pos;
	int			map_width;
	int			map_height;
	char		**two_d_map;
	mlx_t		*mlx;
	mlx_image_t	*roof;
	mlx_image_t	*floor;
	mlx_image_t	*north;
	mlx_image_t	*east;
	mlx_image_t	*south;
	mlx_image_t	*west;
}	t_game;

void	ft_hooks(mlx_key_data_t keydata, t_game *game);

//srcs/utils.c
void	print_dbl_ptr(char **ptr);

#endif