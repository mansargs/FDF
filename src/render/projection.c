/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:00:27 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 02:12:54 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	top_view(t_fdf *data)
{
	data->iso = false;
	data->perspective = false;
	data->top_view = true;
	data->angle_x = 0.0;
	data->angle_y = 0.0;
	data->angle_z = 0.0;

}

void	iso(t_fdf *data)
{
	data->iso = true;
	data->top_view = false;
	data->perspective = false;
}

void	perspect(t_fdf *data)
{
	data->iso = false;
	data->top_view = false;
	data->perspective = true;
	data->angle_x = 0.0;
	data->angle_y = 0.0;
	data->angle_z = 0.0;
}

void	isometric(t_point *start, t_point *end, t_fdf *data)
{
	int	prev_x;

	prev_x = start->x;
	start->x = (start->x - start->y) * cos(ANGLE_30) + data->shift_x;;
	start->y = (prev_x + start->y) * sin(ANGLE_30) - start->z+ data->shift_y;
	prev_x = end->x;
	end->x = (end->x - end->y) * cos(ANGLE_30) + data->shift_x;
	end->y = (prev_x + end->y) * sin(ANGLE_30) - end->z+ data->shift_y;
}

void	perspective(t_point *start, t_point *end)
{
	if (start->z + FOCAL != 0)
	{
		start->x = (start->x * FOCAL) / (start->z + FOCAL);
		start->y = (start->y * FOCAL) / (start->z + FOCAL);
	}
	if (end->z + FOCAL != 0)
	{
		end->x = (end->x * FOCAL) / (end->z + FOCAL);
		end->y = (end->y * FOCAL) / (end->z + FOCAL);
	}
}
