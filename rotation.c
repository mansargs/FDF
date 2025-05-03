/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 01:05:21 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 02:51:29 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void rotate_y_axis(t_point *start, t_point *end, const t_fdf *data)
{
	float prev_x;

	prev_x = start->x;
	start->x = start->x * cos(data->angle_y) + start->z * sin(data->angle_y);
	start->z = -prev_x * sin(data->angle_y) + start->z * cos(data->angle_y);
	prev_x = end->x;
	end->x = end->x * cos(data->angle_y) + end->z * sin(data->angle_y);
	end->z = -prev_x * sin(data->angle_y) + end->z * cos(data->angle_y);
}

void rotate_z_axis(t_point *start, t_point *end, const t_fdf *data)
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
