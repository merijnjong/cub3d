/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:23:18 by mjong             #+#    #+#             */
/*   Updated: 2025/05/22 18:27:06 by dkros            ###   ########.fr       */
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

# define INPUT_ERROR "\033[1;31mError, wrong input\
	\nCorrect input:./cub3d maps/map.cub\n\033[0m"
# define MAP_ERROR "\033[1;31mError, invalid map\
	\nCorrect map format: maps/map.cub\n\033[0m"
# define SCREEN_WIDTH 1600
# define SCREEN_HEIGHT 1000
# define BLOCK_SIZE 20
# define INT_MAX 2147483647

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
	int			dir;
	int			map_width;
	int			map_height;
	char		**two_d_map;
	mlx_t		*mlx;
	mlx_image_t	*roof;
	mlx_image_t	*player;
	mlx_image_t *fov;
	mlx_image_t *gamefield;
	mlx_image_t	*background;
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
void		draw_player(t_game *game, int x, int y, int color);
double		draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color);
void		draw_line_angle(mlx_image_t *img, int x, int y, int length, double angle_deg, int color);
void		draw_game_line(t_game *game, int wall_height, int screenx, int x, bool hit_vertical, double raydirx, double raydiry);
double		cast_ray(t_game *game, int start_x, int start_y, double angle_deg, int max_distance, bool *hit_vertical, double *hit_x, double *hit_y);
void		move_right(t_game *game, double angle_rad);
void		move_left(t_game *game, double angle_rad);
void		move_forward(t_game *game, double angle_rad);
void		move_backwards(t_game *game, double angle_rad);
void		exit_game(t_game *game);
bool		is_aplha(char c);
void		make_image(t_game *game);

//srcs/utils.c
void	print_dbl_ptr(char **ptr);
bool	is_wall(t_game *g, int px, int py);
bool	in_bounds(t_game *g, int x, int y);

#endif