/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:41 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/24 13:11:54 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	valid_file_name(const char *file)
{
	size_t start = ft_strlen(file) - 4;
	if (!ft_strncmp(file + start, ".fdf", 4))
		return (SUCCESS);
	return (FAIL);
}

static int	count_columns_rows(const char *file_name, int *row)
{
	int		fd;
	int		col;
	char	*line;
	int		words;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	col = 0;
	*row = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		++col;
		words = count_words(line, ' ');
		if (words > *row)
			*row = words;
		free(line);
	}
	close(fd);
	return (col);
}

int	main(int argc, char *argv[])
{
	int	fd;
	int	col;
	int	row;
	
	if (argc != 2 || !valid_file_name(argv[1]))
	{
		ft_putendl_fd("Invalid argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	col = count_columns_rows(argv[1], &row);
	return (EXIT_SUCCESS);
}
