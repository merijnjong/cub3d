/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjong <mjong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:32:14 by mjong             #+#    #+#             */
/*   Updated: 2025/06/26 16:36:20 by mjong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

char	*join_lines(char **lines)
{
	char	*result;
	char	*line_with_newline;
	char	*new_result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = -1;
	while (lines[++i])
	{
		line_with_newline = ft_strjoin(lines[i], "\n");
		if (!line_with_newline)
		{
			free(result);
			return (NULL);
		}
		new_result = ft_strjoin(result, line_with_newline);
		free(line_with_newline);
		free(result);
		if (!new_result)
			return (NULL);
		result = new_result;
	}
	return (result);
}

int	tex_col_check(t_game *game, char **lines)
{
	t_tex_col	tex_col;
	int			i;

	i = 0;
	ft_bzero(&tex_col, sizeof(tex_col));
	while (lines[i])
	{
		if (ft_strncmp(lines[i], "NO", 2) == 0
			|| ft_strncmp(lines[i], "SO", 2) == 0
			|| ft_strncmp(lines[i], "WE", 2) == 0
			|| ft_strncmp(lines[i], "EA", 2) == 0)
			check_texture_line(game, lines[i], &tex_col);
		else if (lines[i][0] == 'F' || lines[i][0] == 'C')
			extract_colour(game, lines[i], &tex_col);
		else if (lines[i][0] == '1' || lines[i][0] == '0' || lines[i][0] == ' ')
			break ;
		else if (lines[i][0] != '\0' && !ft_isspacec(lines[i][0]))
		{
			ft_printf("\033[1;31mError: invalid identifier in line: \
\"%s\"\n\033[0m", lines[i]);
			exit(1);
		}
		i++;
	}
	return (i);
}

char	*read_cub_lines(char *filename)
{
	int		fd;
	char	*content;
	char	*line;

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

void	extract_and_validate_map(t_game *game, char **lines, char *file_content,
		int start_idx)
{
	t_tex_col	tex_col;
	char		*map_start;
	char		*map_str;
	char		**split_tmp;

	ft_bzero(&tex_col, sizeof(tex_col));
	map_start = ft_strnstr(file_content, lines[start_idx],
			ft_strlen(file_content));
	if (!map_start || has_internal_empty_line(map_start))
		exit_free(lines, file_content, MAP_NL_ERROR);
	map_str = join_lines(lines + start_idx);
	if (!map_str)
		exit_free(lines, file_content, "Error: failed to join map lines\n");
	split_tmp = ft_split(map_str, '\n');
	if (!split_tmp)
	{
		free(map_str);
		exit_free(lines, file_content, "Error: failed to split map_str\n");
	}
	assign_maps(game, split_tmp);
	free_split(split_tmp);
	free(map_str);
	if (!game->two_d_map || !game->two_d_map_check)
		exit_free(lines, NULL, "Error: failed to duplicate map\n");
	count_map_dimensions(game, &tex_col);
}

void	parse_cub_file(t_game *game, char *filename)
{
	char		**lines;
	char		*file_content;
	int			start_idx;

	file_content = read_cub_lines(filename);
	if (!file_content)
		exit(ft_printf("Error: failed to read file\n"));
	lines = ft_split(file_content, '\n');
	if (!lines)
	{
		free(file_content);
		exit(ft_printf("Error: failed to split .cub content\n"));
	}
	start_idx = tex_col_check(game, lines);
	if (game->tex_col_check < 6)
	{
		free_split(lines);
		free(file_content);
		exit(ft_printf(TEX_COL_ERROR));
	}
	extract_and_validate_map(game, lines, file_content, start_idx);
	free_split(lines);
	free(file_content);
}
