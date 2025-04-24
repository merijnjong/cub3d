/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:24:30 by mjong             #+#    #+#             */
/*   Updated: 2025/04/24 15:55:40 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

char	*join_lines(char **lines)
{
	char	*result;
	char	*temp;
	char	*line_with_newline;
	int		i;

	result = NULL;
	i = 0;
	while (lines[i])
	{
		line_with_newline = ft_strjoin2(lines[i], "\n");
		if (!line_with_newline)
			return (NULL);
		temp = ft_strjoin2(result, line_with_newline);
		free(line_with_newline);
		result = temp;
		i++;
	}
	return (result);
}

char	*read_cub_lines(char *filename)
{
	int		fd;
	char	*line;
	char	*content;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(MAP_ERROR);
		exit(1);
	}
	content = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		content = ft_strjoin2(content, line);
		free(line);
	}
	close(fd);
	return (content);
}

void	parse_cub_file(t_game *game, char *filename)
{
	char	*file_content;
	char	**lines;
	char	*map_str;
	int		i;
	int		has_texture;
	int		has_colour;

	has_texture = 0;
	has_colour = 0;
	file_content = read_cub_lines(filename);
	lines = ft_split(file_content, '\n');
	free(file_content);
	if (!lines)
		exit(ft_printf("Error: failed to split .cub content\n"));
	i = 0;
	while (lines[i])
	{
		if (ft_strncmp(lines[i], "NO", 2) == 0 || ft_strncmp(lines[i], "SO", 2) == 0
			|| ft_strncmp(lines[i], "WE", 2) == 0 || ft_strncmp(lines[i], "EA", 2) == 0)
		{
			assign_texture(game, lines[i]);
			has_texture++;
		}
		else if (lines[i][0] == 'F' || lines[i][0] == 'C')
		{
			extract_colour(game, lines[i]);
			has_colour++;
		}
		else if (lines[i][0] == '1' || lines[i][0] == '0' || lines[i][0] == ' ')
			break ;
		else
			exit(ft_printf(TEX_ERROR));
		i++;
	}

	if (has_texture < 4)
	{
		free_split(lines);
		exit(ft_printf(TEX_ERROR));
	}
	if (has_colour < 2)
	{
		free_split(lines);
		exit(ft_printf(COL_ERROR));
	}
	map_str = join_lines(lines + i);
	game->two_d_map = ft_split(map_str, '\n');
	game->two_d_map_check = ft_split(map_str, '\n');
	free(map_str);
	count_map_dimensions(game);
	// free_split(lines);
}

int	cub_check(char *line)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(line);
	if (len < 4)
		return (1);
	i = len - 4;
	if (line[i] != '.' || line[i + 1] != 'c'
		|| line[i + 2] != 'u' || line[i + 3] != 'b')
		return (1);
	return (0);
}
