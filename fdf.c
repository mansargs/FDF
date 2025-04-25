/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:41 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/25 17:32:00 by mansargs         ###   ########.fr       */
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
		exit(errno);
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
		++*row;
		words = count_words(line, ' ');
		if (words > *col)
			*col = words;
		free(line);
	}
	close(fd);
}

static void	create_matrixes(int fd, int col, int row)
{
	int		**matrix_data;
	t_rgb	**color;

	if (fd == -1)
	{
		perror("");
		exit(errno);
	}
	matrix_data = generate_data_matrix(col, row);
	color = generate_color_matrix(col, row);
	if (!color)
	{
		cleanup_matrix(matrix_data, NULL, row);
		perror("");
		exit (errno);
	}
	fill_matrix(matrix_data, color, row, fd);
	
}

int	main(int argc, char *argv[])
{
	int		fd;
	int		col;
	int		row;

	if (argc != 2 || !valid_file_name(argv[1]))
	{
		ft_putendl_fd("Invalid argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	count_columns_rows(fd, &row, &col);
	fd = open(argv[1], O_RDONLY);
	create_matrixes(fd, col, row);
	return (EXIT_SUCCESS);
}
