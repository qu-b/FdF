/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:56:20 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/31 17:04:34 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Orthographic Projection
void	orth_proj(t_v3d *v3d, t_v3d *projection, int len)
{
	int		i;
	float	orth_pmatrix[3][3];

	init_matrix(orth_pmatrix);
	orth_pmatrix[0][0] = 1;
	orth_pmatrix[1][1] = 1;
	i = 0;
	while (i < len)
	{
		projection[i] = mult_mat(v3d[i], orth_pmatrix);
		i++;
	}
}

// Isometric Projection
void	isometric(t_map *map)
{
	map->sphere = 0;
	map->angle[X] = 30;
	map->angle[Y] = 330;
	map->angle[Z] = 30;
	map->bend = 0;
	map->source.coord[X] = 1080 / 2;
	map->source.coord[Y] = 720 / 2;
}

// Parallel Projection
void	parallel(t_map *map)
{
	map->sphere = 0;
	map->angle[X] = 90;
	map->angle[Y] = 0;
	map->angle[Z] = 0;
	map->bend = 0;
	map->source.coord[X] = 1080 / 2;
	map->source.coord[Y] = 720 / 2;
}

// Spherical Projection
void	spherize(t_fdf *fdf, t_v3d *v3d)
{
	int	i;

	i = 0;
	while (i < fdf->map.n_points)
	{
		v3d[i].coord[X] = (fdf->map.radius + v3d[i].coord[Z]) * \
		cos(v3d[i].polar[LONG]) * sin(v3d[i].polar[LAT]);
		v3d[i].coord[Y] = (fdf->map.radius + v3d[i].coord[Z]) * \
		sin(v3d[i].polar[LONG]) * sin(v3d[i].polar[LAT]);
		v3d[i].coord[Z] = (fdf->map.radius + v3d[i].coord[Z]) * \
		cos(v3d[i].polar[LAT]);
		i++;
	}
}

// Scale z-axis to modify altitude
void	z_scale(t_v3d *v3d, float scalar, int len)
{
	int	i;

	i = 0;
	if (scalar != 0)
		while (i < len)
		{
			v3d[i].coord[Z] /= scalar;
			i++;
		}
}

// Bend
void	bend(t_v3d *v3d, int len, float range)
{
	int		i;
	float	bend;

	i = 0;
	while (i < len)
	{
		bend = ((v3d[i].coord[X] * v3d[i].coord[X]) * (range)) + \
		(v3d[i].coord[Y] * v3d[i].coord[Y]) * (range);
		v3d[i].coord[Z] = v3d[i].coord[Z] - bend;
		i++;
	}
}