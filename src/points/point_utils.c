/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:10:05 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 19:10:48 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!data->perspective)
	{
		rotate_x_axis(&start, &end, data);
		rotate_y_axis(&start, &end, data);
	}
	rotate_z_axis(&start, &end, data);
	if (data->iso)
		isometric(&start, &end, data);
	if (data->perspective)
		perspective(&start, &end);
	bresenham(&start, &end, data);
}
