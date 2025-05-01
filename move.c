/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:17 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/01 21:31:08 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move(t_fdf *data, int move_step_x, int move_step_y)
{
	data->move_y += move_step_y;
	data->move_x += move_step_x;
	ft_bzero(data->img.addr, data->img.line_length * WIN_HEIGHT);
	create_image(data);
}

void	zoom(t_fdf * data, float zoom_step)
{
	int	i;
	int	j;

	if (data->zoom + zoom_step == 0)
		data->zoom += 2 * zoom_step;
	else
		data->zoom += zoom_step;
	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			data->matrix[i][j].z *= zoom_step;
		}
	}
	data->step *= zoom_step;
	ft_bzero(data->img.addr, data->img.line_length * WIN_HEIGHT);
	create_image(data);
}

void	change_z(t_fdf *data, int z_step)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			printf("z ---------> %d\n", data->matrix[i][j].z);
			if (data->matrix[i][j].z != 0)
			{
				//printf("z ---------> %d\n", data->matrix[i][j].z);
				if (data->matrix[i][j].z + z_step == 0)
					data->matrix[i][j].z += z_step * 2;
				else
					data->matrix[i][j].z += z_step;
			}
		}
	}
	ft_bzero(data->img.addr, data->img.line_length * WIN_HEIGHT);
	create_image(data);
}
