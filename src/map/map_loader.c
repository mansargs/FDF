/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:05:50 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 21:45:50 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	create_matrix(int fd, t_fdf *data)
{
	char	*line;
	char	*file_lines;
	int		words;


	*file_lines = ft_strdup("");
	if (!file_lines)
	{
		perror("");
		exit(errno);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (invalid_character(line))
			safe_exit_from_file(fd, line, errno);
		++data->height;
		words = count_words(line, ' ');
		if (words > data->width)
			data->width = words;
		file_lines = ft_gnl_strjoin(file_lines, line);
		if (!file_lines)
		{
			safe_exit_from_file(fd, line, errno);
			exit(errno);
		}
		free(line);
	}
	close(fd);
	read_file_from_line()
}

static void	read_file_from_line(char *file_lines, t_fdf *data)
{
	char	**split;

	split = ft_split(file_lines, '\n');
	free(file_lines);
	if(!split)
	{
		perror("");
		exit(errno);
	}
	data->step = 30;
	data->zoom = 3;
	data->iso = true;
	data->shift_x = WIN_WIDTH / 2;
	data->shift_y = WIN_HEIGHT / 4;
	generate_point_matrix(data);
	fill_matrix(fd, data);
}

void	fill_matrix(int fd, t_fdf *data)
{
	char	*str;
	int		i;
	size_t	len;

	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		len = ft_strlen(str);
		if (len > 0 && str[len - 1] == '\n')
			str[len - 1] = '\0';
		if (!split_and_fill(data->matrix[i], str))
		{
			cleanup_matrix(data->matrix, data->height);
			get_next_line(-1);
			ft_putendl_fd("Problem with the memory or invalid content",
				STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		++i;
	}
}

