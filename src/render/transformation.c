/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:02:21 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 17:01:19 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	rotate_x_axis(t_point *start, t_point *end, const t_fdf *data)
{
	float	prev_y;

	prev_y = start->y;
	start->y = start->y * cos(data->angle_x) - start->z * sin(data->angle_x);
	start->z = prev_y * sin(data->angle_x) + start->z * cos(data->angle_x);
	prev_y = end->y;
	end->y = end->y * cos(data->angle_x) - end->z * sin(data->angle_x);
	end->z = prev_y * sin(data->angle_x) + end->z * cos(data->angle_x);
}

void	rotate_y_axis(t_point *start, t_point *end, const t_fdf *data)
{
	float	prev_x;

	prev_x = start->x;
	start->x = start->x * cos(data->angle_y) + start->z * sin(data->angle_y);
	start->z = -prev_x * sin(data->angle_y) + start->z * cos(data->angle_y);
	prev_x = end->x;
	end->x = end->x * cos(data->angle_y) + end->z * sin(data->angle_y);
	end->z = -prev_x * sin(data->angle_y) + end->z * cos(data->angle_y);
}

void	rotate_z_axis(t_point *start, t_point *end, const t_fdf *data)
{
	float	prev_x;
	float	prev_y;

	prev_x = start->x;
	prev_y = start->y;
	start->x = prev_x * cos(data->angle_z) - prev_y * sin(data->angle_z);
	start->y = prev_x * sin(data->angle_z) + prev_y * cos(data->angle_z);
	prev_x = end->x;
	prev_y = end->y;
	end->x = prev_x * cos(data->angle_z) - prev_y * sin(data->angle_z);
	end->y = prev_x * sin(data->angle_z) + prev_y * cos(data->angle_z);
}

void	zoom(t_fdf *data, float zoom_delta, int step_delta)
{
	if (data->zoom + zoom_delta != 0 && data->zoom + zoom_delta != 10)
	{
		data->zoom += zoom_delta;
		if (data->zoom < 1)
			data->zoom = 1;
		data->step += step_delta;
		if (data->step < 1)
			data->step = 1;
	}
}

void	reset_all_changing(t_fdf *data)
{
	data->step = 30;
	data->zoom = 3;
	data->iso = true;
	data->shift_x = WIN_WIDTH / 2;
	data->shift_y = WIN_HEIGHT / 4;
	data->iso = true;
	data->top_view = false;
	data->perspective = false;
	data->angle_x = 0.0;
	data->angle_y = 0.0;
	data->angle_z = 0.0;
}
