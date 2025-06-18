/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:23:18 by mjong             #+#    #+#             */
/*   Updated: 2025/06/18 18:04:22 by dkros            ###   ########.fr       */
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
# define WALK_SPEED 2
# define TURN_SPEED 4.0


typedef struct s_line_data_t
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	dy;
}	t_line_data;

typedef struct s_game
{
	int			x_pos;
	int			y_pos;
	int			dir;
	int			tex_col_check;
	int			map_width;
	int			map_height;
	int			invalid_map;
	char		**two_d_map;
	char		**two_d_map_check;
	bool		should_refresh;
	uint32_t	floor_colour;
	uint32_t	ceiling_colour;
	mlx_t		*mlx;
	mlx_image_t	*roof;
	mlx_image_t	*player;
	mlx_image_t	*fov;
	mlx_image_t	*gamefield;
	mlx_image_t	*background;
	mlx_image_t	*map;
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*east;
	mlx_image_t	*west;
	t_line_data	c;
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

// executing/move.c
void	handle_input(void *param);

// void	ft_hooks(mlx_key_data_t keydata, t_game *game);

// executing/display.c
void	make_image(t_game *game);

// executing/drawing.c
void	draw_gamefield(t_game *game);
void	draw_player(t_game *game, int x, int y);
void	draw_map(t_game *game, int i, int j);
void	draw_background(t_game *game, int color_1, int color_2);

// executing/calculations.c
bool		is_wall(t_game *g, int px, int py);
double		cast_ray(t_game *game, int start_x, int start_y, double angle_deg, int max_distance, bool *hit_vertical, double *hit_x, double *hit_y);
void		draw_game_line(t_game *game, int wall_height, int screen_x, int tex_x, bool hit_vertical, double rayDirX, double rayDirY);
uint32_t	get_shaded_color(uint32_t pixel, int dist, bool hit_vertical);
double		clamp(double v, double lo, double hi);

// executing/utils.c
void	my_pixel_put(mlx_image_t *img, int x, int y, int color);
bool	is_alpha(char c);

// executing/execution.c
void		exit_game(t_game *game);
mlx_image_t	*draw_square(t_game *data, int x, int y, int size, int color);
bool		in_bounds(t_game *g, int x, int y);

//srcs/utils.c
void	print_dbl_ptr(char **ptr);
void	free_split(char **arr);
void	exit_free(char **lines, char *content, const char *msg);
void	assign_maps(t_game *game, char **split_tmp);

#endif