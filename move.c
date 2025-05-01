/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:17 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/01 18:14:53 by mansargs         ###   ########.fr       */
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

void	zoom(t_fdf * data, int zoom_step)
{
	if (data->step + zoom_step && data->step + zoom_step != 300)
		data->step += zoom_step;
	ft_bzero(data->img.addr, data->img.line_length * WIN_HEIGHT);
	create_image(data);
}
