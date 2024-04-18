/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:41:10 by marvin            #+#    #+#             */
/*   Updated: 2023/02/06 11:25:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Scales all vectors by the scalar s.
void	scale(t_v3d *v3d, int s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		v3d[i].coord[X] *= s;
		v3d[i].coord[Y] *= s;
		v3d[i].coord[Z] *= s;
		i++;
	}
}

// Translates all vectors by the vector v.
void	translate(t_v3d *v3d, t_v3d v, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		v3d[i].coord[X] += v.coord[X];
		v3d[i].coord[Y] += v.coord[Y];
		v3d[i].coord[Z] += v.coord[Z];
		i++;
	}
}

// Rotate around x-axis
void	x_rot(t_v3d *vectors, t_v3d *projection, int angle, int len)
{
	int		i;
	float	rad;
	float	pmatrix[3][3];

	rad = angle * M_PI / 180;
	init_matrix(pmatrix);
	pmatrix[0][0] = 1;
	pmatrix[1][1] = cos(rad);
	pmatrix[1][2] = -sin(rad);
	pmatrix[2][1] = sin(rad);
	pmatrix[2][2] = cos(rad);
	i = 0;
	while (i < len)
	{
		projection[i] = mult_mat(vectors[i], pmatrix);
		i++;
	}
}

// Rotate around y-axis
void	y_rot(t_v3d *vectors, t_v3d *projection, int angle, int len)
{
	int		i;
	float	rad;
	float	pmatrix[3][3];

	rad = angle * M_PI / 180;
	init_matrix(pmatrix);
	pmatrix[0][0] = cos(rad);
	pmatrix[0][2] = sin(rad);
	pmatrix[1][1] = 1;
	pmatrix[2][0] = -sin(rad);
	pmatrix[2][2] = cos(rad);
	i = 0;
	while (i < len)
	{
		projection[i] = mult_mat(vectors[i], pmatrix);
		i++;
	}
}

// Rotate around z-axis
void	z_rot(t_v3d *vectors, t_v3d *projection, int angle, int len)
{
	int		i;
	float	rad;
	float	pmatrix[3][3];

	rad = angle * M_PI / 180;
	init_matrix(pmatrix);
	pmatrix[0][0] = cos(rad);
	pmatrix[0][1] = -sin(rad);
	pmatrix[1][0] = sin(rad);
	pmatrix[1][1] = cos(rad);
	pmatrix[2][2] = 1;
	i = 0;
	while (i < len)
	{
		projection[i] = mult_mat(vectors[i], pmatrix);
		i++;
	}
}
