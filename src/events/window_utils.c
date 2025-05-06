/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:12:34 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/06 22:51:54 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

static int	render_loop(t_fdf *data)
{
	if (data->redraw)
	{
		ft_bzero(data->img.addr, data->img.line_length * WIN_HEIGHT);
		create_image(data);
		data->redraw = false;
	}
	return (0);
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
	mlx_hook(data->win, DESTROY, 0, close_win, data);
	mlx_hook(data->win, KEY_PRESS, 1L << 0, keypress_handler, data);
	mlx_loop_hook(data->mlx, render_loop, data);
	mlx_loop(data->mlx);
}
