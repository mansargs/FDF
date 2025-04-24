/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:35:31 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/24 19:15:33 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cleanup_matrix(int	**matrix, t_rgb **color, int col)
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
	i = -1;
	if (color)
	{
		while (++i < col)
		{
			free(color[i]);
			color[i] = NULL;
		}
		free(color);
	}
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
			cleanup_matrix(matrix_data, NULL, i);
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
			cleanup_matrix(NULL, color, i);
			return (NULL);
		}
	}
	return (color);
}


void	fill_into_color(t_rgb *color, int idx, const char *hex)
{
	int	i;
	int	hex;

	i = 2;
	

}

int	split_and_fill(char *matrix, t_rgb * color, char *str)
{
	char	**split;
	char	**data;
	int		i;

	i = -1;
	split = ft_split(str, ' ');
	while (split[++i])
	{
		if (invalid_cell_content(str))
			return (free(str), FAIL);
		data = ft_split(str, ',');
		if (!data)
			return (free(str), FAIL);
		matrix[i] = ft_atoi(data[0]);
		fill_into_color(color, i, data[1]);
	}

}

void	fill_matrix(int	**matrix_data, t_rgb **color, int col, int row, int fd);
{
	char	*str;

	if (fd == -1)
	{
		cleanup_matrix(matrix_data, color, col);
		perror("");
		exit(errno);
	}
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break;

	}


}
