/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:18:17 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/01 17:03:37 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move(t_fdf *data, int move_step_x, int move_step_y)
{
	data->move_y += move_step_y;
	data->move_x += move_step_x;
	ft_bzero(data->img.addr, data->img.line_length * WIN_HEIGHT);
	create_image(data);
}
