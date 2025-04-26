/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:41 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/26 19:54:35 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/Xlib.h>

static void	count_columns_rows(int fd, t_info *matrix)
{
	char	*line;
	int		words;

	if (fd == -1)
	{
		perror("");
		exit(errno);
	}
	matrix->col = 0;
	matrix->row = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (invalid_charachter(line))
			safe_exit_from_file(fd, line);
		++matrix->row;
		words = count_words(line, ' ');
		if (words > matrix->col)
			matrix->col = words;
		free(line);
	}
	close(fd);
}

static void	create_matrixes(int fd, t_info *matrix)
{
	if (fd == -1)
	{
		perror("");
		exit(errno);
	}
	generate_data_matrix(matrix);
	if (!generate_color_matrix(matrix))
	{
		cleanup_matrix(matrix->data, NULL, matrix->row);
		perror("");
		exit (errno);
	}
	fill_matrix(fd, matrix);
}

void	print_matrix(int **data, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%2d ", data[i][j]);
		}
		printf("\n");
	}
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_info	matrix;

	if (argc != 2 || !valid_file_name(argv[1]))
	{
		ft_putendl_fd("Invalid argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	count_columns_rows(fd, &matrix);
	fd = open(argv[1], O_RDONLY);
	create_matrixes(fd, &matrix);
	open_window	(&matrix, argv[1]);
	return (EXIT_SUCCESS);
}
