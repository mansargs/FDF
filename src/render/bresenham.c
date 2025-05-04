/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:04:12 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 14:40:15 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	interpolate(int	color1, int color2, int cur_step, int tot_step)
{
	int		rgb1[3];
	int		rgb2[3];
	int		final_rgb[3];
	float	ratio;

	if (!tot_step)
		ratio = 0;
	else
		ratio = (float)cur_step / tot_step;
	rgb1[0] = (color1 >> 16) & 0xFF;
	rgb1[1] = (color1 >> 8) & 0xFF;
	rgb1[2] = color1 & 0xFF;
	rgb2[0] = (color2 >> 16) & 0xFF;
	rgb2[1] = (color2 >> 8) & 0xFF;
	rgb2[2] = color2 & 0xFF;
	final_rgb[0] = rgb1[0] + (rgb2[0] - rgb1[0]) * ratio;
	final_rgb[1] = rgb1[1] + (rgb2[1] - rgb1[1]) * ratio;
	final_rgb[2] = rgb1[2] + (rgb2[2] - rgb1[2]) * ratio;
	return ((final_rgb[0] << 16) | (final_rgb[1] << 8) | final_rgb[2]);
}

static void	init_bresenham_data(int *dif_and_dp, int *step, const t_point *s, const t_point *e)
{
	dif_and_dp[0] = abs(e->x - s->x);
	dif_and_dp[1] = abs(e->y - s->y);
	step[0] = 1 - 2 * (s->x > e->x);
	step[1] = 1 - 2 * (s->y > e->y);
	dif_and_dp[2] = dif_and_dp[0] - dif_and_dp[1];
	step[3] = fmax(dif_and_dp[0], dif_and_dp[1]);
	step[2] = 0;
}

void	bresenham(t_point *start, t_point *end, t_fdf *data)
{
	int	dif_and_dp[4];
	int	step[4];

	//printf("start ----> (%d, %d)\n end ------>(%d, %d)\n", start->x, start->y, end->x, end->y);
	init_bresenham_data(dif_and_dp, step, start, end);
	while (1)
	{
		start->color = interpolate(start->color, end->color, step[2], step[3]);
		put_pixel_to_image(data, start);
		if (start->x == end->x && start->y == end->y)
			break ;
		dif_and_dp[3] = 2 * dif_and_dp[2];
		if (dif_and_dp[3] > -dif_and_dp[1])
		{
			dif_and_dp[2] -= dif_and_dp[1];
			start->x += step[0];
		}
		if (dif_and_dp[3] < dif_and_dp[0])
		{
			dif_and_dp[2] += dif_and_dp[0];
			start->y += step[1];
		}
		++step[2];
	}
}
