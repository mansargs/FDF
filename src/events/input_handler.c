/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:13:36 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 15:21:54 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	close_win(t_fdf *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	cleanup_matrix(data->matrix, data->height);
	exit(EXIT_SUCCESS);
}

static void	continue_search(int	keycode, t_fdf *data)
{
	if (keycode == KEY_T)
		top_view(data);
	else if (keycode == KEY_I)
		iso(data);
	else if (keycode == KEY_X && !data->perspective)
		data->angle_x += 0.04;
	else if (keycode == KEY_Y && !data->perspective)
		data->angle_y += 0.04;
	else if (keycode == KEY_Z)
		data->angle_z += 0.04;
	else if (keycode == KEY_P)
		data->perspective = true;
	else if (keycode == KEY_R)
		reset_all_changing(data);
}

int	keypress_handler(int keycode, t_fdf *data)
{
	if (keycode == ESC)
			close_win(data);
	if (keycode == UP || keycode == KEY_W)
		data->shift_y -= SHIFT;
	else if (keycode == DOWN || keycode == KEY_S)
		data->shift_y += SHIFT;
	else if (keycode == LEFT || keycode == KEY_A)
		data->shift_x -= SHIFT;
	else if (keycode == RIGHT || keycode == KEY_D)
		data->shift_x += SHIFT;
	else if (keycode == KEY_J)
		zoom(data, ZOOM_STEP, STEP);
	else if (keycode == KEY_K)
		zoom(data, -ZOOM_STEP, -STEP);
	else
		continue_search(keycode, data);
	ft_bzero(data->img.addr, data->img.line_length * WIN_HEIGHT);
	create_image(data);
	return (0);
}
