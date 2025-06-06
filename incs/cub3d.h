/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merijnjong <merijnjong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:23:18 by mjong             #+#    #+#             */
/*   Updated: 2025/06/06 17:03:41 by merijnjong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <sys/time.h>
# include "MLX42/MLX42.h"
# include "../incs/libft.h"

# define INPUT_ERROR "\033[1;31mError: Wrong input\
	\nCorrect input: ./cub3d maps/map.cub\n\033[0m"
# define MAP_ERROR "\033[1;31mError: Invalid map name\
	\nMake sure your input is the correct map name\n\033[0m"
# define MAP_NL_ERROR "\033[1;31mError: Invalid map\
	\nMake sure your map is contiguous and has no consecutive newlines\n\033[0m"
# define FLOOD_FILL_ERROR "\033[1;31mError: Invalid map\
	\nMake sure your map is\n1. Enclosed by walls (1)\
	\n2. Has at least one player position (N, E, S or W)\
	\n3. Is completely filled out inside the walls (1) by floors (0)\n\033[0m"
# define PLAYER_ERROR "\033[1;31mError: Player is on the edge of the map or there is no player\
	\nMake sure your player exists and is within map bounds\n\033[0m"
# define TEX_COL_ERROR "\033[1;31mError: Missing textures or colours\
	\nMake sure your .cub file has all the required textures and colours \
(NO, SO, WE, EA) and (F, C)\n\033[0m"
# define TEX_ERROR "\033[1;31mError: Missing textures\
	\nMake sure your .cub file has all the required textures \
(NO, SO, WE, EA)\n\033[0m"
# define COL_ERROR "\033[1;31mError: Missing colours\
	\nMake sure your .cub file has all the required colours (F, C)\n\033[0m"
# define SCREEN_WIDTH 1600
# define SCREEN_HEIGHT 1000
# define BLOCK_SIZE 20
# define INT_MAX 2147483647

typedef struct s_line_data_t
{
    int x1;
    int x2;
    int y1;
    int y2;
    int dy;
}   t_line_data;

typedef struct s_game
{
	int			x_pos;
	int			y_pos;
	int         dir;
	int			map_width;
	int			map_height;
	int			tex_col_check;
	int			invalid_map;
	char		**two_d_map;
	char		**two_d_map_check;
    t_line_data c;
	uint32_t	floor_colour;
	uint32_t	ceiling_colour;
	mlx_t		*mlx;
	mlx_image_t *roof;
    mlx_image_t *player;
    mlx_image_t *fov;
    mlx_image_t *gamefield;
    mlx_image_t *background;
    mlx_image_t *img;
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*east;
	mlx_image_t	*west;
}	t_game;

//srcs/parsing
void	extract_colour(t_game *game, char *line);
void	parse_cub_file(t_game *game, char *filename);
void	count_map_dimensions(t_game *game);
void	assign_texture(t_game *game, char *line);

//srcs/parsing/parsing_utils.c
int		has_internal_empty_line(char *str);
int		cub_check(char *line);
void	find_and_validate_player(t_game *game);
int		count_lines(char **map);
char	**dup_map(char **map, int height);

void	ft_hooks(mlx_key_data_t keydata, t_game *game);

void	exit_game(t_game *game);
void	make_image(t_game *game);
void	draw_player(t_game *game, int x, int y, int color);
bool	is_wall(t_game *g, int px, int py);
void	draw_map(t_game *game, int i, int j);
void	draw_background(t_game *game, int color_1, int color_2);

//srcs/utils.c
void	print_dbl_ptr(char **ptr);
void	free_split(char **arr);

#endif