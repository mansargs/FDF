/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:49 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/30 01:38:59 by lenovo           ###   ########.fr       */
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
	int	z;
	int	color;
}		z_clr;

typedef struct
{
	int	x;
	int	y;
	int	z;
	int	color;
}			t_point;



typedef struct
{
	z_clr		**matrix;
	int			height;
	int			width;
	int			step;
	void		*mlx;
	void		*win;
	t_data		*img;
}		fdf;


# define WIN_HEIGHT 1200
# define WIN_WIDTH 1500

// cleaning functions
void	cleanup_matrix(z_clr	**matrix, int row);
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
