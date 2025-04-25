/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:49 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/25 17:21:59 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_rgb;

# define TRUE 1
# define FALSE 0

// cleaning functions
void	cleanup_matrix(int	**matrix, t_rgb **color, int row);
void	free_split(char **arr);
void	safe_exit_from_file(int fd, char *line);

//matrix
int		**generate_data_matrix(int col, int row);
t_rgb	**generate_color_matrix(int col, int row);
void	fill_matrix(int	**matrix_data, t_rgb **color, int row, int fd);

// validation
int	valid_file_name(const char *file);
int	invalid_charachter(const char *str);
int	invalid_cell_content(const char *str);

#endif
