/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:49 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/27 02:52:29 by lenovo           ###   ########.fr       */
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

typedef struct s_info
{
	int	**data;
	int	**color;
	int	col;
	int	row;
}		t_info;

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
#define IMG_WIDTH 1700

// cleaning functions
void	cleanup_matrix(int	**matrix, int **color, int row);
void	free_split(char **arr);
void	safe_exit_from_file(int fd, char *line);

//matrix
void	generate_data_matrix(t_info *matrix);
int		generate_color_matrix(t_info *matrix);
void	fill_matrix(int fd, t_info *matrix);

// validation
int		valid_file_name(const char *file);
int		invalid_charachter(const char *str);
int		invalid_cell_content(const char *str);

void	open_window(t_info *matrix, const char *win_name);

#endif
