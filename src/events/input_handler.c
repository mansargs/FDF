/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:13:36 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 19:13:39 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	keypress_handler(int keycode, t_fdf *data)
{
	printf("keycode -->%d\n", keycode);
	if (keycode == Escape)
			close_win(data);
	if (keycode == Up)
		data->shift_y -= SHIFT;
	else if (keycode == Down)
		data->shift_y += SHIFT;
	else if (keycode == Left)
		data->shift_x -= SHIFT;
	else if (keycode == Right)
		data->shift_x += SHIFT;
	else if (keycode == M_ZOOM)
		zoom(data, ZOOM_STEP, STEP);
	else if (keycode == N_UNZOOM)
		zoom(data, -ZOOM_STEP, -STEP);
	else if (keycode == 116)
		top_view(data);
	else if (keycode == 105)
		iso(data);
	else if (keycode == 106)
		data->angle_x += 0.04;
	else if (keycode == 107)
		data->angle_y += 0.04;
	else if (keycode == 108)
		data->angle_z += 0.04;
	else if (keycode == 112)
		data->perspective = true;
	ft_bzero(data->img.addr, data->img.line_length * WIN_HEIGHT);
	create_image(data);
	return (0);
}
