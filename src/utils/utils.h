/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:24:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 02:45:17 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include "../includes/structes.h"
# include "../../library/libft/libft.h"
# include "../../library/gnl/get_next_line.h"
# include <stdarg.h>

// Memory utils
void	free_split(char **arr);
void	cleanup_matrix(t_z_clr	**matrix, int row);
void	safe_exit_from_file(int fd, char *line);

// Validation utils

bool	valid_file_name(const char *file);
bool	invalid_character(const char *str);
bool	invalid_cell_content(const char *str);

#endif
