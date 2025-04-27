/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:40:53 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/27 22:24:16 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	size_t	start;

	start = ft_strlen(file) - 4;
	if (!ft_strncmp(file + start, ".fdf", 4))
		return (true);
	return (false);
}

bool	invalid_charachter(const char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (!(((*str >= 9 && *str <= 13) || *str == ' ')
				|| (*str >= 48 && *str <= 57)
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
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
		++i;
	if (!str[i])
		return (false);
	if (str[i] == ',' && valid_hex(str + i + 1))
		return (false);
	return (true);
}
