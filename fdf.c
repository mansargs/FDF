/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:41 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/24 17:40:33 by mansargs         ###   ########.fr       */
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
	fd = open(argv[1], O_RDONLY);
	matrix_data = generate_data_matrix(col, row);
	color = generate_color_matrix(col, row);
	if (!color)
	{
		deallocate_data_matrix(matrix_data, col);
		perror("");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
