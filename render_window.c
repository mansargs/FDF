/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:16:54 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/27 22:26:35 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void bresenham(int x0, int y0, int x1, int y1, t_fdf *data) {

	x0 *= ZOOM;
	x1 *= ZOOM;
	y0 *= ZOOM;
	y1 *= ZOOM;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;

	int err = (dx > dy ? dx : -dy) / 2;
	int err2;

	while (1) {
		my_mlx_pixel_put(data->img, x0, y0, 0xffffff);

		if (x0 == x1 && y0 == y1)
			break;

		err2 = err;

		if (err2 > -dx) {
			err -= dy;
			x0 += sx;
		}

		if (err2 < dy) {
			err += dx;
			y0 += sy;
		}
	}
}

void	draw(t_fdf *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			bresenham(x, y, x, y + 1, data);
			bresenham(x, y, x + 1, y, data);
			++x;
		}
		++y;
	}
	bresenham(x, 0, x, y, data);
	bresenham(0, y, x, y, data);
}

void	create_image(t_fdf *data)
{
	t_data img;

	img.img = mlx_new_image(data->mlx, data->width * ZOOM + 1, data->height * ZOOM + 1);
	if (!img.img)
	{
		ft_putendl_fd("Promblem with the creating image", STDERR_FILENO);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		cleanup_matrix(data->matrix, data->color, data->height);
		exit(EXIT_FAILURE);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	data->img = &img;
	draw(data);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_loop(data->mlx);
}

void	open_window(t_fdf *data, const char *win_name)
{
	if (ft_strrchr(win_name, '/'))
		win_name = ft_strrchr(win_name, '/') + 1;
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putendl_fd("Problem with the connecting mlx", STDERR_FILENO);
		cleanup_matrix(data->matrix, data->color, data->height);
		exit(EXIT_FAILURE);
	}
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, ft_substr(win_name, 0, ft_strlen(win_name) - 4));
	if (!data->win)
	{
		ft_putendl_fd("Problem with the opening window", STDERR_FILENO);
		mlx_destroy_display(data->mlx);
		cleanup_matrix(data->matrix, data->color, data->height);
		exit(EXIT_FAILURE);
	}
	create_image(data);
	mlx_loop(data->mlx);
}
