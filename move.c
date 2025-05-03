/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:17 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 17:45:57 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_fdf *data, float zoom_delta, int step_delta)
{
	if (data->zoom +zoom_delta != 0 && data->zoom + zoom_delta != 10)
	{
		data->zoom += zoom_delta;
		if (data->zoom < 1)
			data->zoom = 1;
		data->step += step_delta;
		if (data->step < 1)
			data->step = 1;
	}
}

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
}
