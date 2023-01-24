/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:18:19 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/24 11:40:25 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#define MAX(a, b) (a > b ? a : b)
#define MOD(a) (a < 0 ? -a : a)

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= fdf->graphics->win_x
			|| y < 0 || y >= fdf->graphics->win_y)
		return ;
	dst = fdf->mlxdata->addr + (y * fdf->mlxdata->line_length 
			+ x * (fdf->mlxdata->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	isometric(t_fdf *fdf, float *x, float *y, int z)
{
	*x = (*x - *y) * cos(fdf->graphics->angle_a);
	*y = (*x + *y) * sin(fdf->graphics->angle_b) - z;
}

void	spherize(t_fdf *fdf, float *x, float *y, int z)
{
	int	i;

	// printf("pre x: %d, \n", (int)(*x));

	i = *y * fdf->map.width + *x;
	*x = (fdf->map.radius + fdf->v3d[i].coord[Z]) * \
	cos(fdf->v3d[i].polar[LONG]) * sin(fdf->v3d[i].polar[LAT]);
	// printf("x: %d, float: %f\n", (int)(*x), fdf->v3d[i].polar[LONG]);
	*y = (fdf->map.radius + fdf->v3d[i].coord[Z]) * \
	sin(fdf->v3d[i].polar[LONG]) * sin(fdf->v3d[i].polar[LAT]);
	z = (fdf->map.radius + fdf->v3d[i].coord[Z]) * \
	cos(fdf->v3d[i].polar[LAT]);
	// printf("LONG: %f, LAT: %f\n", fdf->v3d[i].polar[LONG], fdf->v3d[i].polar[LAT]);

}

void plan(t_fdf *fdf, float *x, float *y, int z)
{
	*x = *x + cos(fdf->graphics->angle_a) * z;
	*y = *y + sin(fdf->graphics->angle_a) * z;
}

void	bresenham(t_fdf *fdf, float x, float y, float x1, float y1)
{
	float	x_step;
	float	y_step;
	int		max;
	float	z;
	float	z1;

	z = (float)fdf->map.matrix[(int)y][(int)x] * fdf->graphics->z_zoom;
	z1 = (float)fdf->map.matrix[(int)y1][(int)x1] * fdf->graphics->z_zoom;

	// printf("z: %f, %f\n", z ,z1);
	if (fdf->graphics->sphere != 1)
	{
		spherize(fdf, &x, &y, z);
		spherize(fdf, &x1, &y1, z1);
	}
	//------ zoom ------
	x *= fdf->graphics->zoom;
	y *= fdf->graphics->zoom;
	x1 *= fdf->graphics->zoom;
	y1 *= fdf->graphics->zoom;
	
	
	//------ color -----
	fdf->graphics->color = (z || z1) ? 0xe80c0c : 0xffffff;
	
	//------ 3D ------

	if (fdf->graphics->iso != 1)
	{
		isometric(fdf, &x, &y, z);
		isometric(fdf, &x1, &y1, z1);
	}
	

	// ----- One Point Projection ----
	// plan(fdf, &x, &y, z);
	// plan(fdf, &x1, &y1, z1);
	
	

	//----- shift -----
	x += fdf->graphics->shift_x;
	x1 += fdf->graphics->shift_x;
	y += fdf->graphics->shift_y;
	y1 += fdf->graphics->shift_y;

	x_step = x1 - x;
	y_step = y1 - y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		my_mlx_pixel_put(fdf, x, y, fdf->graphics->color);
		x += x_step;
		y += y_step;
	}
	
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (i < map_points(fdf->map))
	{
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
			{
				// v3d_bresenham(fdf, fdf->v3d[i], fdf->v3d[i + 1]);
				bresenham(fdf, x, y, x + 1, y);
				// draw2(fdf, fdf->v3d[i], fdf->v3d[i + 1]);
			}
			if (y < fdf->map.height - 1)
			{
				// v3d_bresenham(fdf, fdf->v3d[i], fdf->v3d[i + 1]);
				bresenham(fdf, x, y, x, y + 1);
				// draw2(fdf, fdf->v3d[i], fdf->v3d[i + 1]);
			}
			x++;
			i++;
		}
		y++;
	}
	}
	mlx_put_image_to_window(fdf->win_ptr, fdf->win_ptr, fdf->mlxdata->img, 0, 0);
}

void	clear_image(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->graphics->win_x)
	{
		j = 0;
		while (j < fdf->graphics->win_y)
		{
			my_mlx_pixel_put(fdf, i, j, fdf->graphics->bg_color);
			j++;
		}
		i++;
	}
}


void	draw2(t_fdf *fdf, t_v3d p, t_v3d p1)
{
	float	sx;
	float	sy;
	int		max;

	sx = p1.coord[X] - p.coord[X];
	sy = p1.coord[Y] - p.coord[Y];
	max = MAX(MOD(sx), MOD(sy));
	sx /= max;
	sy /= max;
	while ((p.coord[X] - p1.coord[X]) || (p.coord[Y] - p1.coord[Y]))
	{
		my_mlx_pixel_put (fdf, p.coord[X], p.coord[Y], fdf->graphics->color);
		p.coord[X] += sx;
		p.coord[Y] += sy;
	}
}