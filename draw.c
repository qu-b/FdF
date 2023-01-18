/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:18:19 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/13 20:31:30 by fcullen          ###   ########.fr       */
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

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.5);
	*y = (*x + *y) * sin(0.5) - z;
}

void	bresenham(t_fdf *fdf, float x, float y, float x1, float y1)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;

	z = fdf->map.matrix[(int)y][(int)x];
	z1 = fdf->map.matrix[(int)y1][(int)x1];

	//------ zoom ------
	x *= fdf->graphics->zoom;
	y *= fdf->graphics->zoom;
	x1 *= fdf->graphics->zoom;
	y1 *= fdf->graphics->zoom;
	//------ color -----
	fdf->graphics->color = (z || z1) ? 0xe80c0c : 0xffffff;
	
	//------ 3D ------
	isometric(&x, &y, z);
	isometric(&x1, &y1, z1);

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
				bresenham(fdf, x, y, x + 1, y);
			if (y < fdf->map.height - 1)
				bresenham(fdf, x, y, x, y + 1);
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