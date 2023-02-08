/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:09:33 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/08 11:53:09 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Check if pixel is within the screen limits
int	pixl_check(t_v3d v)
{
	if (v.coord[X] > 1080 || v.coord[X] < 0)
		return (0);
	if (v.coord[Y] > 720 || v.coord[Y] < 0)
		return (0);
	return (1);
}

// Bresenham
int	bresenham(t_fdf *fdf, t_v3d start, t_v3d end)
{
	float	dx;
	float	dy;
	int		pixels;
	int		len;
	t_v3d	new;

	if (!pixl_check(start) && !pixl_check(end))
		return (0);
	dx = end.coord[X] - start.coord[X];
	dy = end.coord[Y] - start.coord[Y];
	pixels = sqrt(dx * dx + dy * dy);
	len = pixels;
	dx /= pixels;
	dy /= pixels;
	new.coord[X] = start.coord[X];
	new.coord[Y] = start.coord[Y];
	while (pixels > 0)
	{
		new.color = gradient(start.color, end.color, len, len - pixels);
		my_mlx_pixel_put(fdf, new.coord[X], new.coord[Y], new.color);
		new.coord[X] += dx;
		new.coord[Y] += dy;
		pixels -= 1;
	}
	return (1);
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
		opaque(v3d_copy, fdf->map.n_points);
	bend(v3d_copy, fdf->map.n_points, fdf->map.bend);
	scale(v3d_copy, fdf->map.scale, fdf->map.n_points);
	translate(v3d_copy, fdf->map.source, fdf->map.n_points);
	orth_proj(v3d_copy, v3d_copy, fdf->map.n_points);
}

// While loop for draw_map, as function had too many lines for norm
void	draw_while(t_fdf *fdf, t_v3d *v3d_copy)
{
	int	i;

	i = 0;
	while (i < fdf->map.n_points)
	{
		if (v3d_copy[i].paint)
		{
			if ((i + 1) % (int)fdf->map.width != 0)
			{
				bresenham(fdf, v3d_copy[i], v3d_copy[i + 1]);
				if (fdf->map.diagonals)
				{
					if ((i / (int)fdf->map.width) != (fdf->map.height - 1))
						bresenham(fdf, v3d_copy[i],
							v3d_copy[i + (int)fdf->map.width + 1]);
				}
			}
			if ((i / (int)fdf->map.width) != (fdf->map.height - 1))
				bresenham(fdf, v3d_copy[i], v3d_copy[i + (int)fdf->map.width]);
		}
		i++;
	}
}

// Draw map
void	draw_map(t_fdf *fdf)
{
	t_v3d	*v3d_copy;

	v3d_copy = malloc(fdf->map.n_points * sizeof(t_v3d));
	if (!v3d_copy)
		return ;
	copy_vec(fdf, fdf->map.v3d, v3d_copy);
	map_info(fdf, v3d_copy);
	draw_while(fdf, v3d_copy);
	mlx_put_image_to_window(fdf->win_ptr, fdf->win_ptr,
		fdf->mlxdata->img, 0, 0);
}
