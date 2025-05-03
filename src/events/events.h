/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 01:34:49 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 02:04:55 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "../render/render.h"

void	open_window(t_fdf *data, char *win_name);
int		close_win(t_fdf *data);
int		keypress_handler(int keycode, t_fdf *data);

#endif
