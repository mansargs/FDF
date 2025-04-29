/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:01:11 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/30 00:59:54 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup_matrix(z_clr	**matrix, int row)
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
