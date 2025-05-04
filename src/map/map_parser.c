/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:08:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 16:58:25 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	default_colors(int *color, int z)
{
	if (z > 0)
		*color = 0x005b96;
	else if (z < 0)
		*color = 0x851e3e;
	else
		*color = 0x83d0c9;
}

static void	fill_into_color(int	*color, int z, const char *hex)
{
	int	i;
	int	digit;
	int	len;

	if (!hex)
	{
		default_colors(color, z);
		return ;
	}
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

bool	split_and_fill(t_z_clr *data, char *str)
{
	char	**split;
	char	**divide;
	int		i;

	i = -1;
	split = ft_split(str, ' ');
	while (split[++i])
	{
		if (invalid_cell_content(split[i]))
			return (free_split(split), false);
		divide = ft_split(split[i], ',');
		if (!divide)
			return (free_split(split), false);
		data[i].z = ft_atoi(divide[0]);
		fill_into_color(&data[i].color, data[i].z, divide[1]);
		free_split(divide);
	}
	return (free_split(split), true);
}
