/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:16:54 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/26 19:33:19 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	create_image(t_info *matrix, void *mlx, void *win)
{
	t_data img;

	img.img = mlx_new_image(mlx, IMG_WIDTH, IMG_HEIGHT);
	if (!img.img)
	{
		ft_putendl_fd("Promblem with the creating image", STDERR_FILENO);
		cleanup_matrix(matrix->data, matrix->color, matrix->row);
		exit(EXIT_FAILURE);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_lenght, &img.endian);
}

void	open_window(t_info *matrix, const char *win_name)
{
	void	*mlx;
	void	*win;

	(void) matrix;
	if (ft_strrchr(win_name, '/'))
		win_name = ft_strrchr(win_name, '/') + 1;
	mlx = mlx_init();
	if (!mlx)
	{
		ft_putendl_fd("Problem with the connecting mlx", STDERR_FILENO);
		cleanup_matrix(matrix->data, matrix->color, matrix->row);
		exit(EXIT_FAILURE);
	}
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, ft_substr(win_name, 0, ft_strlen(win_name) - 4));
	if (!win)
	{
		ft_putendl_fd("Problem with the opening window", STDERR_FILENO);
		cleanup_matrix(matrix->data, matrix->color, matrix->row);
		exit(EXIT_FAILURE);
	}
	create_image(matrix, mlx, win);
	mlx_loop(mlx);
}
