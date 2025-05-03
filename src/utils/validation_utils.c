/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:53:33 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/04 01:27:51 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static bool	valid_hex(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	else
		return (false);
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || (str[i] >= 'a' && str[i] <= 'f')
				|| (str[i] >= 'A' && str[i] <= 'F')))
			return (false);
		++i;
	}
	return (true);
}

bool	valid_file_name(const char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (false);
	if (!ft_strncmp(file + len - 4, ".fdf", 4))
		return (true);
	return (false);
}

bool	invalid_character(const char *str)
{
	while (*str)
	{
		if (!(((*str >= 9 && *str <= 13) || *str == ' ')
				|| ft_isdigit(*str)
				|| (*str >= 'a' && *str <= 'f')
				|| (*str >= 'A' && *str <= 'F') || *str == '+' || *str == '-'
				|| *str == ',' || *str == 'x'))
			return (true);
		++str;
	}
	return (false);
}

bool	invalid_cell_content(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (ft_isdigit(str[i]))
		++i;
	if (!str[i])
		return (false);
	if (str[i] == ',' && valid_hex(str + i + 1))
		return (false);
	return (true);
}
