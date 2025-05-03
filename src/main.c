/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:17:19 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 19:17:20 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char *argv[])
{
	int		fd;
	t_fdf	data;

	if (argc != 2 || !valid_file_name(argv[1]))
	{
		ft_putendl_fd("Invalid argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_memset(&data, 0, sizeof(t_fdf));
	fd = open(argv[1], O_RDONLY);
	count_columns_rows(fd, &data);
	fd = open(argv[1], O_RDONLY);
	create_matrixes(fd, &data);
	open_window(&data, argv[1]);
	return (EXIT_SUCCESS);
}
