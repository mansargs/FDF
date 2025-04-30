/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:19:45 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/30 21:20:16 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	generate_point_matrix(t_fdf *data)
{
	int	i;

	data->matrix = (t_z_clr **)malloc(sizeof(t_z_clr *) * data->height);
	if (!data->matrix)
	{
		perror("");
		exit(errno);
	}
	i = -1;
	while (++i < data->height)
	{
		data->matrix[i] = ft_calloc(data->width, sizeof(t_z_clr));
		if (!data->matrix[i])
		{
			cleanup_matrix(data->matrix, i);
			perror("");
			exit(errno);
		}
	}
}

static void	fill_into_color(int	*color, const char *hex)
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
		*color += digit << (4 * (len - i));
	}
}

static bool	split_and_fill(t_z_clr *data, char *str)
{
	char	**split;
	char	**divide;
	int		i;

	i = -1;
	split = ft_split(str, ' ');
	while (split[++i])
	{
		if (invalid_cell_content(split[i]))
			return (free(str), free_split(split), false);
		divide = ft_split(split[i], ',');
		if (!divide)
			return (free(str), free_split(split), false);
		data[i].z = ft_atoi(divide[0]);
		fill_into_color(&data[i].color, divide[1]);
		free_split(divide);
	}
	return (free(str), free_split(split), true);
}

void	fill_matrix(int fd, t_fdf *data)
{
	char	*str;
	int		i;
	size_t	len;

	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		len = ft_strlen(str);
		if (len > 0 && str[len - 1] == '\n')
			str[len - 1] = '\0';
		if (!split_and_fill(data->matrix[i], str))
		{
			cleanup_matrix(data->matrix, data->height);
			get_next_line(-1);
			ft_putendl_fd("Problem with the memory or invalid content",
				STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		++i;
	}
}
