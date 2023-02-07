/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:52:02 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/07 13:25:35 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Returns the number of points on the map.
int	map_points(t_map *map)
{
	return (map->width * map->height);
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

// Converts the n*m integer matrix to 3D vectors.
void	matrix_to_v3d(t_fdf *fdf, t_v3d *points)
{
	int		x;
	int		y;
	int		i;
	int		j;

	x = 0;
	y = 0;
	i = 0;
	j = 1;
	while (y < fdf->map.height)
	{
		while (x < fdf->map.width)
		{
			points[i].coord[X] = x - fdf->map.width / 2;
			points[i].coord[Y] = j - fdf->map.height / 2;
			points[i].coord[Z] = fdf->map.matrix[y][x];
			points[i].paint = 1;
			x++;
			i++;
		}
		x = 0;
		y++;
		j++;
	}
}
