/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:18:19 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/20 20:06:32 by fcullen          ###   ########.fr       */
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

void	spherize(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < map_points(fdf->map))
	{
		fdf->v3d[i].coord[X] = (fdf->map.radius + fdf->v3d[i].coord[Z]) * \
		cos(fdf->v3d[i].polar[LONG]) * sin(fdf->v3d[i].polar[LAT]);
		fdf->v3d[i].coord[Y] = (fdf->map.radius + fdf->v3d[i].coord[Z]) * \
		sin(fdf->v3d[i].polar[LONG]) * sin(fdf->v3d[i].polar[LAT]);
		fdf->v3d[i].coord[Z] = (fdf->map.radius + fdf->v3d[i].coord[Z]) * \
		cos(fdf->v3d[i].polar[LAT]);
		i++;
	}
}

void plan(t_fdf *fdf, float *x, float *y, int z)
{
	*x = *x + cos(fdf->graphics->angle_a) * z;
	*y = *y + sin(fdf->graphics->angle_a) * z;
}

// void	globe(t_fdf *fdf, float *x, float *y, int z)
// {
// 	int	r;

// 	r = 100;
// 	*x = *x * cos(fdf->graphics->angle_a) * sin(fdf->graphics->angle_b) * z - cos(fdf->graphics->angle_a) * *y;
// 	*y = -*y * sin(fdf->graphics->angle_a) - z *  sin(fdf->graphics->angle_a); 
// }

void	v3d_bresenham(t_fdf *fdf, t_v3d start, t_v3d end)
{
	t_v3d	delta;
	t_v3d	pixl;
	int		pixels;
	int		len;

	delta.coord[X] = end.coord[X] - start.coord[X];
	delta.coord[Y] = end.coord[Y] - start.coord[Y];
	printf("%d\n", delta.coord[X]);
	pixels = sqrt(delta.coord[X] * delta.coord[X] + 
					delta.coord[Y] * delta.coord[Y]);
	printf("%d\n", pixels);
	len = pixels;
	if (pixels > 0)
	{delta.coord[X] /= pixels;
	delta.coord[Y] /= pixels;}
	pixl.coord[X] = start.coord[X];
	pixl.coord[Y] = start.coord[Y];
	while (pixels > 0)
	{
		// pixel.color = gradient(start.color, end.color, len, len - pixels);
		my_mlx_pixel_put(fdf, delta.coord[X], 
					delta.coord[Y], fdf->graphics->color);
		pixl.coord[X] += delta.coord[X];
		pixl.coord[Y] += delta.coord[Y];
		pixels = pixels - 1;
	}
}

void	bresenham(t_fdf *fdf, float x, float y, float x1, float y1)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;

	z = fdf->map.matrix[(int)y][(int)x] * fdf->graphics->z_zoom;
	z1 = fdf->map.matrix[(int)y1][(int)x1] * fdf->graphics->z_zoom;

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
	if (fdf->graphics->sphere == 0)
	{
		spherize(fdf);
		x = fdf->v3d->coord[X];
		y = fdf->v3d->coord[Y];
		z = fdf->v3d->coord[Z];
		
		// isometric(fdf, &x, &y, z);
		// isometric(fdf, &x1, &y1, z1);
		// spherize(fdf, &x1, &y1, z1);
	}

	// ----- One Point Projection ----
	// plan(fdf, &x, &y, z);
	// plan(fdf, &x1, &y1, z1);

	// ------ Globe ------
	// globe(fdf, &x, &y, z);
	// globe(fdf, &x1, &y1, z1);

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

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
			{
				// v3d_bresenham(fdf, fdf->v3d[0], fdf->v3d[map_points(fdf->map)]);
				bresenham(fdf, x, y, x + 1, y);
			}
			if (y < fdf->map.height - 1)
			{
				// v3d_bresenham(fdf, fdf->v3d[0], fdf->v3d[map_points(fdf->map)]);
				bresenham(fdf, x, y, x, y + 1);
				}
			x++;
		}
		y++;
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
