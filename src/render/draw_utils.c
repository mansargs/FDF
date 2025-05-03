/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:58:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 01:54:53 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	put_pixel_to_image(t_fdf *data, t_point *start)
{
	char	*pixel;

	if (start->x < 0 || start->y < 0 || start->x >= WIN_WIDTH
		|| start->y >= WIN_HEIGHT)
		return ;
	pixel = (data->img.addr + (start->y * data->img.line_length
				+ start->x * (data->img.bpp / 8)));
	*(unsigned int *)pixel = start->color;
}

static void	draw_matrix(t_fdf *data)
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
