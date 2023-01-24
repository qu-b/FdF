/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:44:58 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/24 12:27:09 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	populate_matrix(t_fdf *fdf, int fd)
{
	char	**split;
	char	*line;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
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

int	**get_matrix(t_fdf *fdf, char *filename)
{
	int	fd;

	
	fd = open(filename, O_RDONLY);	
	fdf->map.matrix = malloc(sizeof(int *) * fdf->map.height);
	populate_matrix(fdf, fd);
	close(fd);
	return (fdf->map.matrix);
}

void	read_file(t_fdf	*fdf, char *filename)
{
	fdf->map.width = get_width(filename);
	fdf->map.height = get_height(filename);
	fdf->map.matrix = get_matrix(fdf, filename);
	fdf->v3d = matrix_to_v3d(fdf);
	cartesian_to_polar(fdf);
}

int	map_points(t_map map)
{
	return (map.width * map.height);
}

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

	points = malloc(map_points(fdf->map) * sizeof(t_v3d));
	if (!points)
		return (0);
	while (y < fdf->map.height)
	{
		while(x < fdf->map.width)
		{
			points[i].coord[X] = x - fdf->map.width / 2;
			points[i].coord[Y] = j - fdf->map.height / 2;
			points[i].coord[Z] = fdf->map.matrix[y][x];
			x++;
			i++;
		}
		x = 0;
		y++;
		j++;
	}
	return (points);
}

void	cartesian_to_polar(t_fdf *fdf)
{
	int		i;
	float	x_step;
	float	y_step;

	i = 0;
	x_step = (M_PI * 2) / (fdf->map.width - 1);
	y_step = M_PI / (fdf->map.height);
	fdf->map.radius = fdf->map.width / (M_PI * 2);
	while (i < map_points(fdf->map))
	{
		// printf("%f, %f, %f\n", fdf->v3d[i].coord[X], fdf->v3d[i].coord[Y], fdf->v3d[i].coord[Z]);
		fdf->v3d[i].polar[LONG] = -(fdf->v3d[i].coord[X]) * x_step;
		if (fdf->v3d[i].coord[Y] > 0)
			fdf->v3d[i].polar[LAT] = ((fdf->v3d[i].coord[Y]) + \
			(fdf->map.height / 2)) * y_step - y_step / 2;
		else
			fdf->v3d[i].polar[LAT] = (fdf->v3d[i].coord[Y] + \
			(fdf->map.height / 2) - 1) * y_step + y_step / 2;

		
		// if (map->points[i].axis[Y] > 0)
		// 	map->points[i].polar[LAT] = ((map->points[i].axis[Y]) + \
		// 	(map->limits.axis[Y] / 2)) * steps_y - 0.5 * steps_y;
		// else
		// 	map->points[i].polar[LAT] = (map->points[i].axis[Y] + \
		// 	(map->limits.axis[Y] / 2) - 1) * steps_y + 0.5 * steps_y;
		// fdf->v3d[i].polar[LAT] = asin((fdf->v3d[i].coord[Z] / fdf->map.radius) * M_PI / 180) * (180 / M_PI);
		// fdf->v3d[i].polar[LONG] = atan2(fdf->v3d[i].coord[X] * (M_PI / 180), fdf->v3d[i].coord[Y] * (M_PI / 180)) * (180 / M_PI);
		printf("i: %d, LONG: %f, LAT: %f\n", i, fdf->v3d[i].polar[LONG], fdf->v3d[i].polar[LAT]);
		// printf("%d\n", i);
		i++;
	}
}

// r = math.sqrt(math.pow(x, 2)+math.pow(y, 2)+math.pow(z, 2))
//     lat = math.asin(z/r)*180/math.pi
//     long = math.atan2(x, y)*180/math.pi