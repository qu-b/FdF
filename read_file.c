/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:44:58 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/20 17:19:44 by fcullen          ###   ########.fr       */
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
	t_v3d	*points;

	x = 0;
	y = 0;
	i = 0;

	points = malloc(map_points(fdf->map) * sizeof(t_v3d));
	if (!points)
		return (0);
	while (y < fdf->map.height)
	{
		while(x < fdf->map.width)
		{
			points[i].coord[X] = x;
			points[i].coord[Y] = y;
			points[i].coord[Z] = fdf->map.matrix[y][x];
			x++;
			i++;
		}
		x = 0;
		y++;
	}
	return (points);
}

void	cartesian_to_polar(t_fdf *fdf)
{
	int		i;
	float	x_step;
	float	y_step;

	i = -1;
	
	x_step = (M_PI * 2) / (fdf->map.width - 1);
	y_step = M_PI / (fdf->map.height);
	fdf->map.radius = fdf->map.width / (M_PI * 2);
	while (++i < map_points(fdf->map))
	{
		fdf->v3d[i].polar[LONG] = -(fdf->v3d[i].coord[X]) * x_step;
		if (fdf->v3d[i].coord[Y] > 0)
			fdf->v3d[i].polar[LAT] = ((fdf->v3d[i].coord[Y]) + (fdf->map.height / 2)) * y_step - 0.5 * y_step;
		else
			fdf->v3d[i].polar[LAT] = (fdf->v3d[i].coord[Y] + (fdf->map.height / 2) - 1) * y_step + 0.5 * y_step;
	}
}
