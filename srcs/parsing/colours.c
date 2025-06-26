/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:40:24 by mjong             #+#    #+#             */
/*   Updated: 2025/06/26 16:07:25 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

uint32_t	make_colour(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	while (ft_isspacec(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspacec(str[i]))
		i++;
	return (str[i] == '\0');
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
	if (!is_valid_number(rgb[0]) || !is_valid_number(rgb[1])
		|| !is_valid_number(rgb[2]))
		exit(ft_printf("Error: RGB components must be numeric\n"));
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
	while (ft_isspacec(line[i]))
		i++;
	if (!ft_isspacec(line[i + 1]))
		exit(ft_printf("Error: invalid character after colour identifier\n"));
	i++;
	while (ft_isspacec(line[i]))
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
