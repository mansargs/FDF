/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:05:50 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/07 21:14:56 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	fill_matrix(char **split, t_fdf *data)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (!split_and_fill(data->matrix[i], split[i]))
		{
			cleanup_matrix(data->matrix, data->height);
			free_split(split);
			get_next_line(-1);
			if (errno == 0)
				ft_putendl_fd("Invalid content", STDERR_FILENO);
			else
				perror("");
			exit(EXIT_FAILURE);
		}
		++i;
	}
	free_split(split);
}

static void	read_file_from_line(char *file_lines, t_fdf *data)
{
	char	**split;

	split = ft_split(file_lines, '\n');
	free(file_lines);
	if (!split)
	{
		perror("");
		exit(errno);
	}
	data->step = 30;
	data->zoom = 3;
	data->redraw = false;
	data->iso = true;
	data->shift_x = WIN_WIDTH / 2;
	data->shift_y = WIN_HEIGHT / 4;
	generate_point_matrix(data);
	fill_matrix(split, data);
}

static void	count_width_height(char *line, t_fdf *data, int fd,
		char **file_lines)
{
	int	words;

	if (invalid_character(line))
		safe_exit_from_file(fd, line, 1);
	++data->height;
	words = count_words(line, ' ');
	if (words > data->width)
		data->width = words;
	*file_lines = ft_gnl_strjoin(*file_lines, line);
	if (!*file_lines)
	{
		safe_exit_from_file(fd, line, 1);
		exit(errno);
	}
	free(line);
}

static char	*read_file_lines(int fd, t_fdf *data)
{
	char	*line;
	char	*file_lines;

	file_lines = ft_strdup("");
	if (!file_lines)
	{
		perror("");
		exit(errno);
	}
	line = get_next_line(fd);
	if (!line)
	{
		free(file_lines);
		safe_exit_from_file(fd, line, 0);
	}
	while (1)
	{
		count_width_height(line, data, fd, &file_lines);
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	close(fd);
	return (file_lines);
}

void	create_matrix(int fd, t_fdf *data)
{
	char	*file_lines;

	file_lines = read_file_lines(fd, data);
	read_file_from_line(file_lines, data);
}
