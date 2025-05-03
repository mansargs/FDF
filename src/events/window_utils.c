/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:12:34 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 19:12:37 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	mlx_hook(data->win, DestroyNotify, 0, close_win, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, keypress_handler, data);
	mlx_loop(data->mlx);
}
