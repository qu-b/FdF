/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:44:58 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/30 13:41:45 by fcullen          ###   ########.fr       */
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
	populate_matrix(fdf, fd);
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
	fdf->map.v3d = matrix_to_v3d(fdf);
	cartesian_to_polar(fdf);
	set_default(fdf, &fdf->map);
}

// Returns the number of points on the map.
int	map_points(t_map *map)
{
	return (map->width * map->height);
}

// Converts the n*m integer matrix to 3D vectors.
t_v3d	*matrix_to_v3d(t_fdf *fdf)
{
	int		x;
	int		y;
	int		i;
	int		j;
	t_v3d	*points;

	x = 0;
	y = 0;
	i = 0;
	j = 1;
	points = malloc(fdf->map.n_points * sizeof(t_v3d));
	if (!points)
		return (0);
	while (y < fdf->map.height)
	{
		while(x < fdf->map.width)
		{
			points[i].coord[X] = x - fdf->map.width / 2;
			points[i].coord[Y] = j - fdf->map.height / 2;
			points[i].coord[Z] = fdf->map.matrix[y][x];
			if (points[i].coord[Z])
				points[i].paint = true;
			x++;
			i++;
		}
		x = 0;
		y++;
		j++;
	}
	return (points);
}

// Converts cartesion coordinates into polar coordinates.
void	cartesian_to_polar(t_fdf *fdf)
{
	int		i;
	float	x_step;
	float	y_step;

	i = 0;
	x_step = (M_PI * 2) / (fdf->map.width - 1);
	y_step = M_PI / (fdf->map.height);
	fdf->map.radius = fdf->map.width / (M_PI * 2);
	while (i < fdf->map.n_points)
	{
		fdf->map.v3d[i].polar[LONG] = -(fdf->map.v3d[i].coord[X]) * x_step;
		if (fdf->map.v3d[i].coord[Y] > 0)
			fdf->map.v3d[i].polar[LAT] = ((fdf->map.v3d[i].coord[Y]) + \
			(fdf->map.height / 2)) * y_step - y_step / 2;
		else
			fdf->map.v3d[i].polar[LAT] = (fdf->map.v3d[i].coord[Y] + \
			(fdf->map.height / 2) - 1) * y_step + y_step / 2;
		i++;
	}
}
