/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:49 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 18:03:04 by mansargs         ###   ########.fr       */
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

typedef struct s_matrix
{
	int	z;
	int	color;
}		t_z_clr;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}		t_point;

typedef struct s_fdf
{
	t_z_clr		**matrix;
	int			height;
	int			width;
	int			step;
	int			shift_x;
	int			zoom;
	bool		iso;
	bool		top_view;
	bool		perspective;
	bool		rotate_x;
	bool		rotate_y;
	bool		rotate_z;
	float		angle_x;
	float		angle_y;
	float		angle_z;
	int			shift_y;
	void		*mlx;
	void		*win;
	t_data		img;
}		t_fdf;

# define WIN_HEIGHT 1200
# define WIN_WIDTH 1500

# ifndef DestroyNotify
#  define DestroyNotify 17
# endif

# ifndef KeyPress
#  define KeyPress 2
# endif

# ifndef KeyPressMask
#  define KeyPressMask 1L << 0
# endif

# ifndef Escape
#  define Escape 65307
# endif

# ifndef Up
#  define Up 65362
# endif

# ifndef Down
#  define Down 65364
# endif

# ifndef Left
#  define Left 65361
# endif

# ifndef Right
#  define Right 65363
# endif

# ifndef SHIFT
#  define SHIFT 15
# endif

# ifndef STEP
#  define STEP 1
# endif

# ifndef ZOOM_STEP
#  define ZOOM_STEP 0.2
# endif

# ifndef M_ZOOM
#  define M_ZOOM 109
# endif

# ifndef N_UNZOOM
#  define N_UNZOOM 110
# endif

# ifndef CHANGE_Z
#  define CHANGE_Z 5
# endif

# ifndef Z_UP
#  define Z_UP 122
# endif

# ifndef Z_DOWN
#  define Z_DOWN 120
# endif

#define FOCAL 100

// cleaning functions
void	cleanup_matrix(t_z_clr	**matrix, int row);
void	free_split(char **arr);
void	safe_exit_from_file(int fd, char *line);

//matrix
void	generate_point_matrix(t_fdf *data);
void	fill_matrix(int fd, t_fdf *data);

// validation
bool	valid_file_name(const char *file);
bool	invalid_character(const char *str);
bool	invalid_cell_content(const char *str);

void	open_window(t_fdf *data, char *win_name);
void	isometric(t_point *start, t_point *end, t_fdf *data);
void	perspective(t_point *start, t_point *end);
void	create_image(t_fdf *data);
void	bresenham(t_point *start, t_point *end, t_fdf *data);

void	zoom(t_fdf * data, float zoom_delta, int step);
void	change_z(t_fdf *data, int z_step);
void	top_view(t_fdf *data);
void	iso(t_fdf *data);
void	perspect(t_fdf *data);

void	rotate_x_axis(t_point *start, t_point *end, const t_fdf *data);
void	rotate_y_axis(t_point *start, t_point *end, const t_fdf *data);
void	rotate_z_axis(t_point *start, t_point *end, const t_fdf *data);

#endif
