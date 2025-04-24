/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:35:31 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/24 17:44:41 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	deallocate_data_matrix(int	**matrix, int col)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while (++i < col)
		{
			free(matrix[i]);
			matrix[i] = NULL;
		}
		free(matrix);
	}
}

void	deallocate_color_matrix(t_rgb **color, int col)
{
	int	i;

	if (!color)
		return ;
	i = -1;
	while (++i < col)
	{
		free(color[i]);
		color[i] = NULL;
	}
	free(color);
}

int	**generate_data_matrix(int col, int row)
{
	int	**matrix_data;
	int	i;
	int	j;

	matrix_data = (int **)malloc((sizeof(int *) * col));
	if (!matrix_data)
	{
		perror("");
		exit(ENOMEM);
	}
	i = -1;
	j = -1;
	while (++i < col)
	{
		matrix_data[i] = ft_calloc(row, sizeof(int));
		if (!matrix_data[i])
		{
			deallocate_data_matrix(matrix_data, i);
			perror("");
			exit(ENOMEM);
		}
	}
	return (matrix_data);
}

t_rgb	**generate_color_matrix(int col, int row)
{
	t_rgb	**color;
	int		i;

	i = -1;
	color = (t_rgb **)malloc(sizeof(t_rgb *) * col);
	if (!color)
		return (NULL);
	while (++i < col)
	{
		color[i] = (t_rgb *)malloc(sizeof(t_rgb) * row);
		if (!color[i])
		{
			deallocate_color_matrix(color, i);
			return (NULL);
		}
	}
	return (color);
}
