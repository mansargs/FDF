/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:35:31 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/27 16:03:07 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	generate_data_matrix(t_fdf *data)
{
	int	i;

	data->matrix = (int **)malloc((sizeof(int *) * data->row));
	if (!data->matrix)
	{
		perror("");
		exit(errno);
	}
	i = -1;
	while (++i < data->row)
	{
		data->matrix[i] = ft_calloc(data->col, sizeof(int));
		if (!data->matrix[i])
		{
			cleanup_matrix(data->matrix, NULL, i);
			perror("");
			exit(errno);
		}
	}
}

int	generate_color_matrix(t_fdf *data)
{
	int		i;

	i = -1;
	data->color = (int **)malloc(sizeof(int *) * data->row);
	if (!data->color)
		return (FALSE);
	while (++i < data->row)
	{
		data->color[i] = ft_calloc(data->col, sizeof(int));
		if (!data->color[i])
		{
			cleanup_matrix(NULL, data->color, i);
			return (FALSE);
		}
	}
	return (TRUE);
}

static void	fill_into_color(int	*color, int idx, const char *hex)
{
	int	i;
	int	digit;
	int	len;

	if (!hex)
		return ;
	i = 1;
	len = 7;
	while (hex[++i])
	{
		if (ft_isdigit(hex[i]))
			digit = hex[i] - '0';
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			digit = hex[i] - 'a' + 10;
		else
			digit = hex[i] - 'A' + 10;
		color[idx] += digit * pow(16, len - i);
	}
}

static int	split_and_fill(int *data, int *color, char *str)
{
	char	**split;
	char	**divide;
	int		i;

	i = -1;
	split = ft_split(str, ' ');
	while (split[++i])
	{
		if (invalid_cell_content(split[i]))
			return (free(str), free_split(split), FALSE);
		divide = ft_split(split[i], ',');
		if (!divide)
			return (free(str), free_split(split), FALSE);
		data[i] = ft_atoi(divide[0]);
		fill_into_color(color, i, divide[1]);
		free_split(divide);
	}
	return (free(str), free_split(split), TRUE);
}

void	fill_matrix(int fd, t_fdf *data)
{
	char	*str;
	int		i;

	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		str[ft_strlen(str) - 1] = '\0';
		if (!split_and_fill(data->matrix[i], data->color[i], str))
		{
			cleanup_matrix(data->matrix, data->color, data->row);
			get_next_line(-1);
			ft_putendl_fd("Problem with the memory or invalid content",
				STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		++i;
	}
}
