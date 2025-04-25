/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:35:31 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/25 17:28:23 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	**generate_data_matrix(int col, int row)
{
	int	**matrix_data;
	int	i;
	int	j;

	matrix_data = (int **)malloc((sizeof(int *) * row));
	if (!matrix_data)
	{
		perror("");
		exit(errno);
	}
	i = -1;
	j = -1;
	while (++i < row)
	{
		matrix_data[i] = ft_calloc(col, sizeof(int));
		if (!matrix_data[i])
		{
			cleanup_matrix(matrix_data, NULL, i);
			perror("");
			exit(errno);
		}
	}
	return (matrix_data);
}

t_rgb	**generate_color_matrix(int col, int row)
{
	t_rgb	**color;
	int		i;

	i = -1;
	color = (t_rgb **)malloc(sizeof(t_rgb *) * row);
	if (!color)
		return (NULL);
	while (++i < row)
	{
		color[i] = (t_rgb *)malloc(sizeof(t_rgb) * col);
		if (!color[i])
		{
			cleanup_matrix(NULL, color, i);
			return (NULL);
		}
	}
	return (color);
}

static void	fill_into_color(t_rgb *color, int idx, const char *hex)
{
	int	i;
	int	j;
	int	digit[6];

	if (!hex)
		return ;
	i = 1;
	j = 0;
	while (hex[++i])
	{
		if (ft_isdigit(hex[i]))
			digit[j] = hex[i] - 48;
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			digit[j] = hex[i] - 87;
		else
			digit[j] = hex[i] - 55;
		++j;
	}
	color[idx].red = digit[0] * 16 + digit[1];
	color[idx].green = digit[2] * 16 + digit[3];
	color[idx].blue = digit[4] * 16 + digit[5];
}

static int	split_and_fill(int *matrix, t_rgb *color, char *str)
{
	char	**split;
	char	**data;
	int		i;

	i = -1;
	split = ft_split(str, ' ');
	while (split[++i])
	{
		if (invalid_cell_content(split[i]))
			return (free(str), free_split(split), FALSE);
		data = ft_split(split[i], ',');
		if (!data)
			return (free(str), free_split(split), FALSE);
		matrix[i] = ft_atoi(data[0]);
		fill_into_color(color, i, data[1]);
		free_split(data);
	}
	return (free(str), free_split(split), TRUE);
}

void	fill_matrix(int	**matrix_data, t_rgb **color, int row, int fd)
{
	char	*str;
	int		i;

	if (fd == -1)
	{
		cleanup_matrix(matrix_data, color, row);
		perror("");
		exit(errno);
	}
	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		str[ft_strlen(str) - 1] = '\0';
		if (!split_and_fill(matrix_data[i], color[i], str))
		{
			cleanup_matrix(matrix_data, color, row);
			get_next_line(-1);
			ft_putendl_fd("Problem with the memory or invalid content", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		++i;
	}
}
