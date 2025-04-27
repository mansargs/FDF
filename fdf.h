/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:49 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/27 15:59:58 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct s_fdf
{
	void	*img;
	int		**matrix;
	int		**color;
	int		col;
	int		row;
	void	*mlx;
	void	*win;
	t_data	*img;
}		t_fdf;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_data;

# define TRUE 1
# define FALSE 0
# define WIN_HEIGHT 1500
# define WIN_WIDTH 2000
# define IMG_HEIGHT 1200
# define IMG_WIDTH 1700

// cleaning functions
void	cleanup_matrix(int	**matrix, int **color, int row);
void	free_split(char **arr);
void	safe_exit_from_file(int fd, char *line);

//matrix
void	generate_data_matrix(t_fdf *data);
int		generate_color_matrix(t_fdf *data);
void	fill_matrix(int fd, t_fdf *data);

// validation
int		valid_file_name(const char *file);
int		invalid_charachter(const char *str);
int		invalid_cell_content(const char *str);

void	open_window(t_fdf *data, const char *win_name);

#endif
