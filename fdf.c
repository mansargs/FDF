/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:31:32 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/23 01:00:42 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	valid_file_name(const char *file)
{
	size_t start = ft_strlen(file) - 4;
	if (!ft_strncmp(file + start, ".fdf", 4))
		return (SUCCESS);
	return (FAIL);
}

int	main(int argc, char *argv[])
{
	if (argc != 2 || !valid_file_name(argv[1]))
	{
		perror(strerror(EINVAL));
		return (EXIT_FAILURE);
	}
}
