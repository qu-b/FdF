/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:09:33 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/02 17:24:00 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Check if pixel is within the screen limits
int	pixl_check(t_v3d v)
{
	if (v.coord[X] > 1080 || v.coord[X] < 0)
		return (0);
	if (v.coord[Y] > 720 ||  v.coord[Y] < 0)
		return (0);
	return (1);
}

// Bresenham
int	bresenham(t_fdf *fdf, t_v3d start, t_v3d end)
{
	float	dx;
	float	dy;
	int		max;
	float	z;
	float	z1;

	if (!pixl_check(start) && !pixl_check(end))
		return (0);
	z = start.coord[Z];
	z1 = end.coord[Z];
	// fdf->map.color = (start.paint || end.paint) ? 0xeee : 0xffffff;
	dx = end.coord[X] - start.coord[X];
	dy = end.coord[Y] - start.coord[Y];
	max = MAX(MOD(dx), MOD(dy));
	dx /= max;
	dy /= max;
	while ((int)(start.coord[X] - end.coord[X]) || (int)(start.coord[Y] - end.coord[Y]))
	{
		my_mlx_pixel_put(fdf, start.coord[X], start.coord[Y], start.color);
		start.coord[X] += dx;
		start.coord[Y] += dy;
	}
	return (1);
}

// This functions takes car of sphere transparency
void	shadow(t_v3d *v3d, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (v3d[i].coord[Z] < 0)
			v3d[i].paint = 0;
		else
			v3d[i].paint = 1;
		i++;
	}
}

// Get map info
void	map_info(t_fdf *fdf, t_v3d	*v3d_copy)
{
	z_scale(v3d_copy, fdf->map.zscale, fdf->map.n_points);
	bend(v3d_copy, fdf->map.n_points, fdf->map.bend);
	if (fdf->map.sphere)
		spherize(fdf, v3d_copy);
	x_rot(v3d_copy, v3d_copy, fdf->map.angle[X], fdf->map.n_points);
	y_rot(v3d_copy, v3d_copy, fdf->map.angle[Y], fdf->map.n_points);
	z_rot(v3d_copy, v3d_copy, fdf->map.angle[Z], fdf->map.n_points);
	if (fdf->map.sphere)
		shadow(v3d_copy, fdf->map.n_points);
	scale(v3d_copy, fdf->map.scale, fdf->map.n_points);
	translate(v3d_copy, fdf->map.source, fdf->map.n_points);
	orth_proj(v3d_copy, v3d_copy, fdf->map.n_points);
}

// Draw map
void	draw_map(t_fdf *fdf)
{
	int	i;
	t_v3d	*v3d_copy;

	i = 0;
	v3d_copy = malloc(fdf->map.n_points * sizeof(t_v3d));
	copy_vec(fdf, fdf->map.v3d, v3d_copy);
	map_info(fdf, v3d_copy);
	// clear_image(fdf);
	while (i < fdf->map.n_points)
	{
		if (v3d_copy[i].paint)
		{
			if ((i + 1) % (int)fdf->map.width != 0)
			{
				bresenham(fdf, v3d_copy[i], v3d_copy[i + 1]);
				// if (meta->map.b_pluslines)
				// {
				// 	if ((i / (int)fdf->map.width) != (fdf->map.height - 1))
				// 		draw_line(fdf, wire[i], wire[i + (int)fdf->map.width + 1]);
				// }
			}
			if ((i / (int)fdf->map.width) != (fdf->map.height - 1))
				bresenham(fdf, v3d_copy[i], v3d_copy[i + (int)fdf->map.width]);
		}
		i++;
	}
	mlx_put_image_to_window(fdf->win_ptr, fdf->win_ptr, fdf->mlxdata->img, 0, 0);
}

