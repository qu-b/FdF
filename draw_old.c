/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:18:19 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/27 17:25:54 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Isometric Matrix Transformation
void	isometric(t_fdf *fdf, float *x, float *y, int z)
{
	*x = (*x - *y) * cos(fdf->map.angle_a);
	*y = (*x + *y) * sin(fdf->map.angle_b) - z;
}

// Spherical Matrix Transformation
void	spherize(t_fdf *fdf, float *x, float *y, int z)
{
	int	i;

	i = *y * fdf->map.width + *x;
	*x = (fdf->map.radius + fdf->v3d[i].coord[Z]) * \
	cos(fdf->v3d[i].polar[LONG]) * sin(fdf->v3d[i].polar[LAT]);
	*y = (fdf->map.radius + fdf->v3d[i].coord[Z]) * \
	sin(fdf->v3d[i].polar[LONG]) * sin(fdf->v3d[i].polar[LAT]);
	z = (fdf->map.radius + fdf->v3d[i].coord[Z]) * \
	cos(fdf->v3d[i].polar[LAT]);
}

// Planar Matrix Transformation
void plan(t_fdf *fdf, float *x, float *y, int z)
{
	*x = *x + cos(fdf->map.angle_a) * z;
	*y = *y + sin(fdf->map.angle_a) * z;
}

// Bresenham's Line Drawing Algorithm
void	bresenham(t_fdf *fdf, float x, float y, float x1, float y1)
{
	float	x_step;
	float	y_step;
	int		max;
	float	z;
	float	z1;

	z = (float)fdf->map.matrix[(int)y][(int)x] * fdf->map.z_zoom;
	z1 = (float)fdf->map.matrix[(int)y1][(int)x1] * fdf->map.z_zoom;

	//------ 3D ------

	if (fdf->map.sphere != 1)
	{
		spherize(fdf, &x, &y, z);
		spherize(fdf, &x1, &y1, z1);
	}
	if (fdf->map.iso != 1)
	{
		isometric(fdf, &x, &y, z);
		isometric(fdf, &x1, &y1, z1);
	}
	// ----- One Point Projection ----
	// plan(fdf, &x, &y, z);
	// plan(fdf, &x1, &y1, z1);

	//------ zoom ------
	x *= fdf->map.zoom;
	y *= fdf->map.zoom;
	x1 *= fdf->map.zoom;
	y1 *= fdf->map.zoom;

	//------ color -----
	fdf->map.color = (z || z1) ? 0xe80c0c : 0xffffff;

	//----- shift -----
	x += fdf->map.shift_x;
	x1 += fdf->map.shift_x;
	y += fdf->map.shift_y;
	y1 += fdf->map.shift_y;

	x_step = x1 - x;
	y_step = y1 - y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		my_mlx_pixel_put(fdf, x, y, fdf->map.color);
		x += x_step;
		y += y_step;
	}
	
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
			{
				bresenham(fdf, x, y, x + 1, y);
			}
			if (y < fdf->map.height - 1)
			{
				bresenham(fdf, x, y, x, y + 1);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->win_ptr, fdf->win_ptr, fdf->mlxdata->img, 0, 0);
}
