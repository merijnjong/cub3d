/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:42:18 by dkros             #+#    #+#             */
/*   Updated: 2025/06/10 16:44:59 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

bool is_wall(t_game *g, int px, int py)
{
    int map_x = px / BLOCK_SIZE;
    int map_y = py / BLOCK_SIZE;

    if (!in_bounds(g, map_x, map_y)) 
        return true;
    return (g->two_d_map[map_y][map_x] == '1');
}

double cast_ray(t_game *game, int start_x, int start_y, double angle_deg, int max_distance, bool *hit_vertical, double *hit_x, double *hit_y)
{
	double rayAngle = fmod(angle_deg * (M_PI/180.0), 2*M_PI);
    if (rayAngle < 0)
		rayAngle += 2*M_PI;
	
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    int mapX = start_x / BLOCK_SIZE;
    int mapY = start_y / BLOCK_SIZE;

    double deltaDistX = fabs(1.0 / rayDirX) * BLOCK_SIZE;
    double deltaDistY = fabs(1.0 / rayDirY) * BLOCK_SIZE;

    int stepX, stepY;
    double sideDistX, sideDistY;
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = ((start_x / (double)BLOCK_SIZE) - mapX) * deltaDistX;
    }
    else
    {
        stepX = +1;
        sideDistX = (mapX + 1.0 - (start_x / (double)BLOCK_SIZE)) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = ((start_y / (double)BLOCK_SIZE) - mapY) * deltaDistY;
    }
    else
    {
        stepY = +1;
        sideDistY = (mapY + 1.0 - (start_y / (double)BLOCK_SIZE)) * deltaDistY;
    }

    bool side;
    while (1)
    {
        if (sideDistX < sideDistY)
        {
			sideDistX += deltaDistX;
            mapX += stepX;
            side = true;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = false;
        }
		
        if (!in_bounds(game, mapX, mapY) || game->two_d_map[mapY][mapX] == '1')
		break;
    }
	
    double perpDist = side
	? (sideDistX - deltaDistX)
        : (sideDistY - deltaDistY);
		
		if (perpDist > (double)max_distance)
        return -1.0;
		
    if (hit_vertical)
	*hit_vertical = side;
	
    if (hit_x)
	*hit_x = start_x + rayDirX * perpDist;

    if (hit_y)
	*hit_y = start_y + rayDirY * perpDist;
	
    return perpDist;
}

double clamp(double v, double lo, double hi)
{
	return v < lo ? lo : v > hi ? hi : v;
}


uint32_t get_shaded_color(uint32_t pixel, int dist, bool hit_vertical)
{
    uint8_t r = (pixel >> 24) & 0xFF;
    uint8_t g = (pixel >> 16) & 0xFF;
    uint8_t b = (pixel >>  8) & 0xFF;
    uint8_t a =  pixel        & 0xFF;

    double shade = 1.0 - (dist * 0.03 / 500.0);
    shade = clamp(shade, 0.0, 1.0);
    if (hit_vertical)
	shade *= 0.9;
	
    r = (uint8_t)(r * shade);
    g = (uint8_t)(g * shade);
    b = (uint8_t)(b * shade);
	
    return (r<<24) | (g<<16) | (b<<8) | a;
}