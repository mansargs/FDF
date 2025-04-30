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

void put_pixel_to_image(fdf *data, t_point *start)
{
	char *pixel;

	if (start->x < 0 || start->y < 0 || start->x >= WIN_WIDTH || start->y >= WIN_HEIGHT)
		return ;
	pixel = (data->img.addr + (start->y * data->img.line_length + start->x * (data->img.bpp / 8)));
	*(unsigned int *)pixel = 0xffffff;
}

void	bresenham(t_point *start, t_point *end, fdf *data)
{
	int	dif[4];
	int	step[2];

	dif[0] = abs(end->x - start->x);
	dif[1] = abs(end->y - start->y);
	step[0] = 1 - 2 * (start->x > end->x);
	step[1] = 1 - 2 * (start->y > end->y);
	dif[2] = dif[0] - dif[1];
	while (1)
	{
		put_pixel_to_image(data, start);
		if (start->x == end->x && start->y == end->y)
			break;
		dif[3] = 2 * dif[2];
		if (dif[3] > -dif[1])
		{
			dif[2] -= dif[1];
			start->x += step[0];
		}
		if (dif[3] < dif[0])
		{
			dif[2] += dif[0];
			start->y += step[1];
		}
	}
}

void	isometric(t_point *start, t_point *end, fdf *data)
{
	int	prev_x;

	prev_x = start->x;
	start->x = (start->x - start->y) * cos(M_PI / 6) + WIN_WIDTH / 2;
	start->y = (prev_x + start->y) * sin(M_PI / 6) - start->z + WIN_HEIGHT / 2;
	prev_x = end->x;
	end->x = (end->x - end->y) * cos(M_PI / 6) + WIN_WIDTH / 2;
	end->y = (prev_x + end->y) * sin(M_PI / 6) - end->z + WIN_HEIGHT / 2;
	printf("start----->(%d, %d)\nend----------->(%d, %d)\n\n", start->x, start->y, end->x, end->y);
	bresenham(start, end, data);
}

void	initialize_points(int y, int x, fdf *data, int vertical)
{
	t_point	start;
	t_point	end;

	start.x = x * data->step;
	start.y = y * data->step;
	start.z = data->matrix[y][x].z;
	start.color = data->matrix[y][x].color;
	if (vertical)
	{
		end.x = x * data->step;
		end.y = (y + 1) * data->step;
		end.z = data->matrix[y + 1][x].z;
		end.color = data->matrix[y + 1][x].color;
	}
	else
	{
		end.x = (x + 1) * data->step;
		end.y = y * data->step;
		end.z = data->matrix[y][x + 1].z;
		end.color = data->matrix[y][x + 1].color;
	}
	isometric(&start, &end, data);
}

void	draw_matrix(fdf *data)
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

void	create_image(fdf *data)
{
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img)
	{
		ft_putendl_fd("Promblem with the creating image", STDERR_FILENO);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		cleanup_matrix(data->matrix, data->height);
		exit(EXIT_FAILURE);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.line_length, &data->img.endian);
	draw_matrix(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_loop(data->mlx);
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
