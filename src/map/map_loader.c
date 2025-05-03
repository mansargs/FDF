/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:05:50 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 19:08:24 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	count_columns_rows(int fd, t_fdf *data)
{
	char	*line;
	int		words;

	if (fd == -1)
	{
		perror("");
		exit(errno);
	}
	data->width = 0;
	data->height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (invalid_character(line))
			safe_exit_from_file(fd, line);
		++data->height;
		words = count_words(line, ' ');
		if (words > data->width)
			data->width = words;
		free(line);
	}
	close(fd);
}

static void	create_matrixes(int fd, t_fdf *data)
{
	if (fd == -1)
	{
		perror("");
		exit(errno);
	}
	data->step = 30;
	data->zoom = 3;
	data->iso = true;
	data->top_view = false;
	data->perspective = false;
	data->angle_x = 0.0;
	data->angle_y = 0.0;
	data->angle_z = 0.0;
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

