/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spike_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkros <dkros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:06:13 by dkros             #+#    #+#             */
/*   Updated: 2025/06/25 17:13:27 by dkros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	average_int(int *arr, int n)
{
	int	i;
	int	total;
	int	avg;

	i = 0;
	total = 0;
	while (i < n)
	{
		total += arr[i];
		i++;
	}
	if (n == 0)
		return (0);
	avg = total / n;
	return (avg);
}

int	has_value_above(int *arr, int n, int limit)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (arr[i] > limit)
			return (1);
		i++;
	}
	return (0);
}

void	get_row_lengths(t_game *game, int *len_arr, int *row_count)
{
	int	i;
	int	len;

	i = 0;
	*row_count = 0;
	while (game->two_d_map[i])
	{
		len = ft_strlen(game->two_d_map[i]);
		len_arr[i] = len;
		(*row_count)++;
		i++;
	}
}

void	count_column_heights(t_game *game, int *heights)
{
	int	y;
	int	x;
	int	line_len;

	y = 0;
	while (y < game->map_height)
	{
		line_len = ft_strlen(game->two_d_map[y]);
		x = 0;
		while (x < line_len)
		{
			if (game->two_d_map[y][x] != ' ' && game->two_d_map[y][x] != '\t')
				heights[x]++;
			x++;
		}
		y++;
	}
}
