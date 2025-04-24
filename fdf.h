/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 09:43:49 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/24 19:00:05 by mansargs         ###   ########.fr       */
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

# define SUCCESS 1
# define FAIL 0

void	safe_exit_from_file(int fd, char *line);
int		invalid_charachter(const char *str);
int		valid_file_name(const char *file);
int		**generate_data_matrix(int col, int row);
t_rgb	**generate_color_matrix(int col, int row);
void	cleanup_matrix(int	**matrix, t_rgb **color, int col);
int	invalid_cell_content(const char *str);

#endif
