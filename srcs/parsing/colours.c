/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merijnjong <merijnjong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:40:24 by mjong             #+#    #+#             */
/*   Updated: 2025/06/20 16:50:11 by merijnjong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

uint32_t	make_colour(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

uint32_t	parse_rgb_string(char *rgb_str)
{
	char	**rgb;
	char	*trimmed;
	int		r;
	int		g;
	int		b;

	trimmed = ft_strtrim(rgb_str, " \n");
	if (!trimmed)
		exit(ft_printf("Error: memory allocation failed\n"));
	rgb = ft_split(trimmed, ',');
	free(trimmed);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		exit(ft_printf("Error: invalid RGB format\n"));
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit(ft_printf("Error: RGB values out of range\n"));
	return (make_colour(r, g, b));
}

void	extract_colour(t_game *game, char *line, t_tex_col *col)
{
	char	*rgb_start;
	int		i;

	i = 0;
	while (line[i] && (ft_isalpha(line[i]) || ft_isspacec(line[i])))
		i++;
	rgb_start = line + i;
	if (line[0] == 'C')
	{
		if (col->c++)
			exit(ft_printf(COL_ERROR));
		game->ceiling_colour = parse_rgb_string(rgb_start);
	}
	else if (line[0] == 'F')
	{
		if (col->f++)
			exit(ft_printf(COL_ERROR));
		game->floor_colour = parse_rgb_string(rgb_start);
	}
	game->tex_col_check++;
}
