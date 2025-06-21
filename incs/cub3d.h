/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merijnjong <merijnjong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:23:18 by mjong             #+#    #+#             */
/*   Updated: 2025/06/21 03:55:32 by merijnjong       ###   ########.fr       */
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
	\n3. Is completely filled out inside the walls (1) by floors (0)\
	\n4. Doesn't have any vertical or horizontal spikes\n\033[0m"
# define PLAYER_ERROR "\033[1;31mError: Player is on the edge of the map or there is no player\
	\nMake sure your player exists and is within map bounds\n\033[0m"
# define TEX_COL_ERROR "\033[1;31mError: Missing textures or colours\
	\nMake sure your .cub file has all the required textures and colours \
(NO, SO, WE, EA) and (F, C)\n\033[0m"
# define TEX_ERROR "\033[1;31mError: Duplicate textures\
	\nMake sure your .cub file has all the required textures and no diplucates \
(NO, SO, WE, EA)\n\033[0m"
# define COL_ERROR "\033[1;31mError: Duplicate colours\
	\nMake sure your .cub file has all the required colours and no diplucates (F, C)\n\033[0m"
# define SCREEN_WIDTH 1600
# define SCREEN_HEIGHT 1000
# define BLOCK_SIZE 20
# define INT_MAX 2147483647
# define WALK_SPEED 2
# define TURN_SPEED 2

typedef struct s_line_data_t
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	dy;
}	t_line_data;

typedef struct s_tex_col
{
	int no;
	int so;
	int we;
	int ea;
	int f;
	int c;
}	t_tex_col;

// typedef struct s_gamefield
// {
// 	const double	half_fov;
// 	const double	angle_start;
// 	const double	delta_angle;
// 	int				screen_x;
// 	double			ray_angle;
// 	double			rad;
// 	double			ray_dir_x;
// 	double			ray_dir_y;
// 	bool			was_vertical;
// 	double			hit_x;
// 	double			hit_y;
// 	double			perp_dist;
// 	int				wall_h;
// 	double			hit_offset;
// 	int				tex_x;
// }	t_gamefield;

// typedef struct s_game_line
// {
// 	mlx_image_t	*tex;
// 	int			mid;
// 	int			half_h;
// 	int			top;
// 	int			bottom;
// 	int			y;
// 	int			tex_y;
// 	int			pixel_index;
// 	int			byte_offset;
// 	uint8_t		*p;
// 	uint8_t		r;
// 	uint8_t		g;
// 	uint8_t		b;
// 	uint8_t		a;
// 	uint32_t	px;
// 	uint32_t	color;
// 	int			wall_height;
// 	int			screen_x;
// 	bool		hit_vertical;
// 	double		ray_dir_x;
// 	double		ray_dir_y;
// }	t_game_line;

typedef struct s_game
{
	int			x_pos;
	int			y_pos;
	int			dir;
	int			map_width;
	int			map_height;
	int			block_size;
	int			invalid_map;
	int			tex_col_check;
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
	t_tex_col	tex_col;
	t_line_data	c;
}	t_game;



//srcs/parsing
void	extract_colour(t_game *game, char *line, t_tex_col *col);
void	parse_cub_file(t_game *game, char *filename);
void	count_map_dimensions(t_game *game);
void	check_texture_line(t_game *game, char *line, t_tex_col *tex);

//srcs/parsing/parsing_utils.c
int		has_internal_empty_line(char *str);
int		cub_check(char *line);
void	find_and_validate_player(t_game *game);
int		count_lines(char **map);

// executing/move.c
void	handle_input(void *param);

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
void	clear_image(mlx_image_t *img);

// executing/execution.c
void		exit_game(t_game *game);
mlx_image_t	*draw_square(t_game *data, int x, int y, int size, int color);
bool		in_bounds(t_game *g, int x, int y);

//srcs/utils.c
void	print_dbl_ptr(char **ptr);
void	free_split(char **arr);
void	exit_free(char **lines, char *content, const char *msg);
void	assign_maps(t_game *game, char **split_tmp);
void	exit_and_print(int code, char *message);
int		get_block_size(t_game *game);



#endif
