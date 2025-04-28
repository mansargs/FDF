/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:49 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/28 13:42:51 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_data;

typedef struct
{
	int	x;
	int	y;
	int	z;
	int	color;
}		t_point;


typedef struct
{
	t_point		**matrix;
	int			height;
	int			width;
	void		*mlx;
	void		*win;
	t_data		*img;
}		fdf;


# define WIN_HEIGHT 700
# define WIN_WIDTH 700
# define ZOOM 20

// cleaning functions
void	cleanup_matrix(t_point	**matrix, int row);
void	free_split(char **arr);
void	safe_exit_from_file(int fd, char *line);

//matrix
void	generate_point_matrix(fdf *data);
void	fill_matrix(int fd, fdf *data);

// validation
bool	valid_file_name(const char *file);
bool	invalid_character(const char *str);
bool	invalid_cell_content(const char *str);

void	open_window(fdf *data, const char *win_name);

#endif
