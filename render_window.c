	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   render_window.c                                    :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2025/04/26 18:16:54 by mansargs          #+#    #+#             */
	/*   Updated: 2025/04/28 12:08:21 by lenovo           ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "fdf.h"

void put_pixel_to_image(fdf *data, int x, int y, int color)
{
	char *pixel;

	if (x < 0 || y < 0 || x > WIN_WIDTH || y > WIN_HEIGHT)
		return ;
	pixel = (data->img->addr + (y * data->img->line_length + x * (data->img->bpp / 8)));
	*(unsigned int *)pixel = color;
}

void isometric(t_point *point, int offset_x, int offset_y)
{
	int prev_x = point->x;
	point->x = (point->x - point->y) * cos(M_PI / 6) + offset_x;
	point->y = (prev_x + point->y) * sin(M_PI / 6) - point->z + offset_y;
}

void bresenham(t_point start, t_point end, fdf *data)
{
    int dif[2];
    int step[2];
    int deviation;
	int offset_x = WIN_WIDTH / 2;
	int offset_y = WIN_HEIGHT / 8;

	isometric(&start, offset_x, offset_y);
	isometric(&end, offset_x, offset_y);
    dif[0] = abs(end.x - start.x);
    dif[1] = abs(end.y - start.y);
    step[0] = (end.x > start.x) ? 1 : (end.x < start.x) ? -1 : 0;
    step[1] = (end.y > start.y) ? 1 : (end.y < start.y) ? -1 : 0;

    deviation = (dif[0] > dif[1]) ? dif[0] / 2 : -dif[1] / 2;

    while (1)
    {
        put_pixel_to_image(data, start.x, start.y, 0xffffff);
        if (start.x == end.x && start.y == end.y)
            break;

        if (2 * deviation > -dif[0])
        {
            deviation -= dif[1];
            start.x += step[0];
        }
        if (2 * deviation < dif[1])
        {
            deviation += dif[0];
            start.y += step[1];
        }
    }
}


void	draw(fdf *data)
{
	int	x;
	int	y;
	y = 0;
	while (y < data->height - 1)
	{
		x = 0;
		while (x < data->width - 1)
		{
			bresenham(data->matrix[y][x], data->matrix[y + 1][x], data);
			bresenham(data->matrix[y][x], data->matrix[y][x + 1], data);
			++x;
		}
		++y;
	}
	if (data->height > 1 && data->width > 1) {
		bresenham(data->matrix[data->height - 1][0], data->matrix[data->height - 1][data->width - 1], data); // Last row
		bresenham(data->matrix[0][data->width - 1], data->matrix[data->height - 1][data->width - 1], data); // Last column
	}
}

void	create_image(fdf *data)
{
	t_data img;
	img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img.img)
	{
		ft_putendl_fd("Promblem with the creating image", STDERR_FILENO);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		cleanup_matrix(data->matrix, data->height);
		exit(EXIT_FAILURE);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	data->img = &img;
	draw(data);
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
}

void	open_window(fdf *data, const char *win_name)
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
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, ft_substr(win_name, 0, ft_strlen(win_name) - 4));
	if (!data->win)
	{
		ft_putendl_fd("Problem with the opening window", STDERR_FILENO);
		mlx_destroy_display(data->mlx);
		cleanup_matrix(data->matrix, data->height);
		exit(EXIT_FAILURE);
	}
	create_image(data);
	mlx_loop(data->mlx);
}
