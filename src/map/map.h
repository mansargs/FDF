/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:58:22 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 17:30:24 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../utils/utils.h"
# include "../includes/defines.h"

void	create_matrix(int fd, t_fdf *data);
void	generate_point_matrix(t_fdf *data);
bool	split_and_fill(t_z_clr *data, char *str);

#endif
