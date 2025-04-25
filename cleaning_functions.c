/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:01:11 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/25 17:09:40 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup_matrix(int	**matrix, t_rgb **color, int row)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while (++i < row)
		{
			free(matrix[i]);
			matrix[i] = NULL;
		}
		free(matrix);
	}
	i = -1;
	if (color)
	{
		while (++i < row)
		{
			free(color[i]);
			color[i] = NULL;
		}
		free(color);
	}
}

void	free_split(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void	safe_exit_from_file(int fd, char *line)
{
	free(line);
	get_next_line(-1);
	close(fd);
	ft_putendl_fd("Invalid characters in file", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
