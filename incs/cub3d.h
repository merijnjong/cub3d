/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:23:18 by mjong             #+#    #+#             */
/*   Updated: 2025/04/24 15:53:44 by mjong            ###   ########.fr       */
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

# define INPUT_ERROR "\033[1;31mError: Wrong input\
	\nCorrect input: ./cub3d maps/map.cub\n\033[0m"
# define MAP_ERROR "\033[1;31mError: Invalid map name\
	\nMake sure your input is the correct map name\n\033[0m"
# define FLOOD_FILL_ERROR "\033[1;31mError: Invalid map\
	\nMake sure your map is\n1. Enclosed by walls (1)\
	\n2. Has at least one player position (N, E, S or W)\
	\n3. Is completely filled out inside the walls (1) by floors (0)\n\033[0m"
# define TEX_COL_ERROR "\033[1;31mError: Missing textures or colours\
	\nMake sure your .cub file has all the required textures and colours \
(NO, SO, WE, EA) and (F, C)\n\033[0m"
# define TEX_ERROR "\033[1;31mError: Missing textures\
	\nMake sure your .cub file has all the required textures \
(NO, SO, WE, EA)\n\033[0m"
# define COL_ERROR "\033[1;31mError: Missing colours\
	\nMake sure your .cub file has all the required colours (F, C)\n\033[0m"

typedef struct s_game
{
	int			x_pos;
	int			y_pos;
	int			map_width;
	int			map_height;
	int			invalid_map;
	char		**two_d_map;
	char		**two_d_map_check;
	uint32_t	floor_colour;
	uint32_t	ceiling_colour;
	mlx_t		*mlx;
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*east;
	mlx_image_t	*west;
}	t_game;

//srcs/parsing
void	extract_colour(t_game *game, char *line);
void	parse_cub_file(t_game *game, char *filename);
void	count_map_dimensions(t_game *game);
int		cub_check(char *line);
void	assign_texture(t_game *game, char *line);

void	ft_hooks(mlx_key_data_t keydata, t_game *game);

//srcs/utils.c
void	print_dbl_ptr(char **ptr);
void	free_split(char **arr);

#endif