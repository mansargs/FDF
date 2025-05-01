/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:17 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/02 03:27:04 by lenovo           ###   ########.fr       */
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
		if (data->step < 5)
			data->step = 5;
	}
}

