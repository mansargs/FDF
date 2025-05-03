/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:53:08 by mansargs          #+#    #+#             */
/*   Updated: 2025/05/03 19:18:46 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_split(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void	cleanup_matrix(t_z_clr	**matrix, int row)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while (++i < row)
		{
			free(matrix[i]);
			matrix[i] = NULL;
		}
		free(matrix);
	}
}

void	safe_exit_from_file(int fd, char *line)
{
	free(line);
	get_next_line(-1);
	close(fd);
	ft_putendl_fd("Invalid characters in file", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
