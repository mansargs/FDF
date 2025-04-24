/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:41 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/24 18:19:12 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	count_columns_rows(int fd, int *row, int *col)
{
	char	*line;
	int		words;

	if (fd == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	*col = 0;
	*row = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (invalid_charachter(line))
			safe_exit_from_file(fd, line);
		++*col;
		words = count_words(line, ' ');
		if (words > *row)
			*row = words;
		free(line);
	}
	close(fd);
}

int	main(int argc, char *argv[])
{
	int		fd;
	int		**matrix_data;
	t_rgb	**color;
	int		col;
	int		row;

	if (argc != 2 || !valid_file_name(argv[1]))
	{
		ft_putendl_fd("Invalid argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	count_columns_rows(fd, &row, &col);
	matrix_data = generate_data_matrix(col, row);
	color = generate_color_matrix(col, row);
	if (!color)
	{
		cleanup_matrix(matrix_data, NULL, col);
		perror("");
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	fill_matrix(matrix_data, color, fd);
	return (EXIT_SUCCESS);
}
