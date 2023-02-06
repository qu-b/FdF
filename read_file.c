/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:44:58 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/06 16:15:16 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Get number of rows from file
int	get_height(char *filename)
{
	int		fd;
	int		height;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	while (get_next_line(fd))
		height++;
	close(fd);
	return (height);
}

// Get number of columns from file
int	get_width(char *filename)
{
	int		fd;
	int		i;
	int		width;
	char	*line;
	char	**split;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	width = 0;
	line = get_next_line(fd);
	i = ft_strlen(line);
	if (line[--i] == '\n')
		line[i] = '\0';
	split = ft_split(line, ' ');
	while (split[width])
		width++;
	close(fd);
	free(line);
	return (width);
}

// Use get_next_line + atoi to populate an integer matrix with a given map
void	populate_matrix(t_fdf *fdf, int fd)
{
	char	**split;
	char	*line;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (j < fdf->map.height)
	{
		line = get_next_line(fd);
		k = ft_strlen(line);
		if (line[--k] == '\n')
			line[k] = '\0';
		split = ft_split(line, ' ');
		fdf->map.matrix[j] = malloc(sizeof(int) * fdf->map.width);
		while (split[i] != 0)
		{
			fdf->map.matrix[j][i] = ft_atoi(split[i]);
			i++;
		}
		i = 0;
		j++;
		dbl_free (split);
	}
}

// Create space in memory for integer matrix to populate it.
int	**get_matrix(t_fdf *fdf, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	fdf->map.matrix = malloc(sizeof(int *) * fdf->map.height);
	if (!fdf->map.matrix)
		return (0);
	populate_matrix(fdf, fd);
	fdf->map.v3d = malloc(fdf->map.n_points * sizeof(t_v3d));
	if (!fdf->map.v3d)
		return (0);
	matrix_to_v3d(fdf, fdf->map.v3d);
	free(fdf->map.matrix);
	close(fd);
	return (fdf->map.matrix);
}

// Get data from file into a usable format.
void	read_file(t_fdf	*fdf, char *filename)
{
	t_map		*map;

	map = malloc(sizeof(*map));
	if (!map)
		exit (1);
	fdf->map = *map;
	fdf->map.width = get_width(filename);
	fdf->map.height = get_height(filename);
	fdf->map.n_points = map_points(&fdf->map);
	fdf->map.matrix = get_matrix(fdf, filename);
	cartesian_to_polar(fdf);
	set_default(fdf, &fdf->map);
}
