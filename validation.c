/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:40:53 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/25 17:04:45 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	valid_hex(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	else
		return (FALSE);
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || (str[i] >= 'a' && str[i] <= 'f')
				|| (str[i] >= 'A' && str[i] <= 'F')))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int	valid_file_name(const char *file)
{
	size_t	start;

	start = ft_strlen(file) - 4;
	if (!ft_strncmp(file + start, ".fdf", 4))
		return (TRUE);
	return (FALSE);
}

int	invalid_charachter(const char *str)
{
	if (!str)
		return (TRUE);
	while (*str)
	{
		if (!(((*str >= 9 && *str <= 13) || *str == ' ')
				|| (*str >= 48 && *str <= 57)
				|| (*str >= 'a' && *str <= 'f')
				|| (*str >= 'A' && *str <= 'F') || *str == '+' || *str == '-'
				|| *str == ',' || *str == 'x'))
			return (TRUE);
		++str;
	}
	return (FALSE);
}

int	invalid_cell_content(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
		++i;
	if (!str[i])
		return (FALSE);
	if (str[i] == ',' && valid_hex(str + i + 1))
		return (FALSE);
	return (TRUE);
}
