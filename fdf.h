/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:49 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/01 16:33:43 by mansargs         ###   ########.fr       */
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
	int			move_x;
	int			move_y;
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

# ifndef MOVE_X
#  define MOVE_X -15
# endif

# ifndef MOVE_Y
#  define MOVE_Y -15
# endif

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
void	create_image(t_fdf *data);

void	move(t_fdf *data, int move_step_x, int move_step_y);

#endif
