/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:47:46 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/06 22:45:34 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTES_H
# define STRUCTES_H

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
	bool		redraw;
	bool		iso;
	bool		top_view;
	bool		perspective;
	float		angle_x;
	float		angle_y;
	float		angle_z;
	int			shift_y;
	void		*mlx;
	void		*win;
	t_data		img;
}		t_fdf;

#endif
