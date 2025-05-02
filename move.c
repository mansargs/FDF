/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:17 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/02 18:10:02 by mansargs         ###   ########.fr       */
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
	data->top_view = true;
}

void	iso(t_fdf *data)
{
	data->iso = true;
	data->top_view = false;
}
