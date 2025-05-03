/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:35:22 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 02:53:23 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_point(int y, int x, t_point *point, t_fdf *data)
{
	point->x = x * data->step;
	point->y = y * data->step;
	point->z = data->matrix[y][x].z * data->zoom;
	point->color = data->matrix[y][x].color;
	if (data->top_view)
	{
		point->x += data->shift_x;
		point->y += data->shift_y;
	}
}

void	initialize_points(int y, int x, t_fdf *data, int vertical)
{
	t_point	start;
	t_point	end;

	init_point(y, x, &start, data);
	if (vertical)
		init_point(y + 1, x, &end, data);
	else
		init_point(y, x + 1, &end, data);
	if (data->iso)
		isometric(&start, &end, data);
	rotate_x_axis(&start, &end, data);
	rotate_y_axis(&start, &end, data);
	rotate_z_axis(&start, &end, data);
	bresenham(&start, &end, data);
}

void	draw_matrix(t_fdf *data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			if (j < data->width -1)
				initialize_points(i, j, data, 0);
			if (i < data->height - 1)
				initialize_points(i, j, data, 1);
		}
	}
}

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
	ft_bzero(data->img.addr, data->img.line_length * WIN_HEIGHT);
	create_image(data);
	return (0);
}

void	create_image(t_fdf *data)
{
	if (!data->img.img)
		data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img)
	{
		ft_putendl_fd("Promblem with the creating image", STDERR_FILENO);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		cleanup_matrix(data->matrix, data->height);
		exit(EXIT_FAILURE);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
	draw_matrix(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	open_window(t_fdf *data, char *win_name)
{
	if (ft_strrchr(win_name, '/'))
		win_name = ft_strrchr(win_name, '/') + 1;
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putendl_fd("Problem with the connecting mlx", STDERR_FILENO);
		cleanup_matrix(data->matrix, data->height);
		exit(EXIT_FAILURE);
	}
	win_name[ft_strlen(win_name) - 4] = '\0';
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, win_name);
	if (!data->win)
	{
		ft_putendl_fd("Problem with the opening window", STDERR_FILENO);
		mlx_destroy_display(data->mlx);
		cleanup_matrix(data->matrix, data->height);
		exit(EXIT_FAILURE);
	}
	create_image(data);
	mlx_hook(data->win, DestroyNotify, 0, close_win, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, keypress_handler, data);
	mlx_loop(data->mlx);
}
