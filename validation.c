/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:40:53 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/24 17:06:47 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	valid_file_name(const char *file)
{
	size_t	start;

	start = ft_strlen(file) - 4;
	if (!ft_strncmp(file + start, ".fdf", 4))
		return (SUCCESS);
	return (FAIL);
}

int	invalid_charachter(const char *str)
{
	if (!str)
		return (SUCCESS);
	while (*str)
	{
		if (!(((*str >= 9 && *str <= 13) || *str == ' ')
				|| (*str >= 48 && *str <= 57)
				|| (*str >= 'a' && *str <= 'f')
				|| (*str >= 'A' && *str <= 'F') || *str == '+' || *str == '-'
				|| *str == ',' || *str == 'x'))
			return (SUCCESS);
		++str;
	}
	return (FAIL);
}

void	safe_exit_from_file(int fd, char *line)
{
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
	close(fd);
	ft_putendl_fd("Invalid characters in file", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
