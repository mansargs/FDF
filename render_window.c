/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:16:54 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/27 17:45:11 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	unsigned int	*pixel;

	pixel = (unsigned int*)img->addr + (y * img->line_length + x * (img->bpp / 8));
	*pixel = color;
}

void	bresenham(float x1, float y1, float x2, float y2, t_fdf *data)
{
	float	dx;
	float	dy;
	float	max;

	x1 *= ZOOM;
	x2 *= ZOOM;
	y1 *= ZOOM;
	y2 *= ZOOM;
	dx = x2 - x1;
	dy = y2 - y1;
	max = fmax(fabs(dx), fabs(dy));
	dx /= max;
	dy /= max;
	while ((int)(x2 - x1) || (int)(y2 - y1))
	{
		my_mlx_pixel_put(data->img, x1, y1, 0xffffff);
		x1 += dx;
		y1 += dy;
	}
}


void	draw(t_fdf *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->row)
	{
		x = 0;
		while (x < data->col)
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

	img.img = mlx_new_image(data->mlx, IMG_WIDTH, IMG_HEIGHT);
	if (!img.img)
	{
		ft_putendl_fd("Promblem with the creating image", STDERR_FILENO);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		cleanup_matrix(data->matrix, data->color, data->row);
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
		cleanup_matrix(data->matrix, data->color, data->row);
		exit(EXIT_FAILURE);
	}
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, ft_substr(win_name, 0, ft_strlen(win_name) - 4));
	if (!data->win)
	{
		ft_putendl_fd("Problem with the opening window", STDERR_FILENO);
		mlx_destroy_display(data->mlx);
		cleanup_matrix(data->matrix, data->color, data->row);
		exit(EXIT_FAILURE);
	}
	create_image(data);
	mlx_loop(data->mlx);
}
