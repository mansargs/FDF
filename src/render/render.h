/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:51:43 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 15:05:00 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../map/map.h"
# include <mlx.h>
# include <math.h>

// Points
void	initialize_points(int y, int x, t_fdf *data, int vertical);
void	put_pixel_to_image(t_fdf *data, t_point *start);
void	create_image(t_fdf *data);

// Rotation and zooming
void	rotate_x_axis(t_point *start, t_point *end, const t_fdf *data);
void	rotate_y_axis(t_point *start, t_point *end, const t_fdf *data);
void	rotate_z_axis(t_point *start, t_point *end, const t_fdf *data);
void	zoom(t_fdf *data, float zoom_delta, int step_delta);

// Projection
void	reset_all_changing(t_fdf *data);
void	top_view(t_fdf *data);
void	iso(t_fdf *data);
void	perspect(t_fdf *data);
void	isometric(t_point *start, t_point *end, t_fdf *data);
void	perspective(t_point *start, t_point *end);

// Line drawing algorithm
void	bresenham(t_point *start, t_point *end, t_fdf *data);

#endif
