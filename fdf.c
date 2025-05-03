/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:41 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 17:37:03 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	main(int argc, char *argv[])
{
	int		fd;
	t_fdf	data;

	if (argc != 2 || !valid_file_name(argv[1]))
	{
		ft_putendl_fd("Invalid argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_memset(&data, 0, sizeof(t_fdf));
	fd = open(argv[1], O_RDONLY);
	count_columns_rows(fd, &data);
	fd = open(argv[1], O_RDONLY);
	create_matrixes(fd, &data);
	open_window(&data, argv[1]);
	return (EXIT_SUCCESS);
}
