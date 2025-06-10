/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:40:58 by dkros             #+#    #+#             */
/*   Updated: 2025/06/10 16:41:51 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

void	my_pixel_put(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		mlx_put_pixel(img, x, y, color);
}

double get_dist(int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	double len = sqrt((double)(pow(dx, 2) + pow(dy, 2)));
	return (len);
}

void draw_line_angle(int x, int y, int length, double angle_deg)
{
	double angle_rad;
	angle_rad = angle_deg * (M_PI / 180.0);

	int x_end;
	int y_end;

	x_end = x + (int)(length * cos(angle_rad));
	y_end = y + (int)(length * sin(angle_rad));

	get_dist(x, y, x_end, y_end);
}

bool is_alpha(char c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return true;
	return false;
}