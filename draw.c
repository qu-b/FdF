/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:09:33 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/30 15:47:45 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Bresenham
void	draw_line(t_fdf *fdf, t_v3d start, t_v3d end)
{
	t_v3d	delta;
	t_v3d	pixel;
	int		pixels;
	int		len;

	fdf->map.color = (start.coord[Z] || end.coord[Z]) ? 0xe80c0c : 0xffffff;
	delta.coord[X] = end.coord[X] - start.coord[X];
	delta.coord[Y] = end.coord[Y] - start.coord[Y];
	pixels = sqrt((delta.coord[X] * delta.coord[X]) + \
			(delta.coord[Y] * delta.coord[Y]));
	len = pixels;
	delta.coord[X] /= pixels;
	delta.coord[Y] /= pixels;
	pixel.coord[X] = start.coord[X];
	pixel.coord[Y] = start.coord[Y];
	// pixel.coord[X] *= fdf->map.zoom;
	// pixel.coord[X] *= fdf->map.zoom;
	while (pixels > 0)
	{
		pixel.color = start.color;
		my_mlx_pixel_put(fdf, pixel.coord[X], pixel.coord[Y], fdf->map.color);
		pixel.coord[X] += delta.coord[X];
		pixel.coord[Y] += delta.coord[Y];
		pixels -= 1;
	}
}

// Bresenham
void	bresenham(t_fdf *fdf, t_v3d start, t_v3d end)
{
	float	dx;
	float	dy;
	int		max;
	float	z;
	float	z1;

	z = start.coord[Z];
	z1 = end.coord[Z];
	fdf->map.color = (start.paint || end.paint) ? 0xeee : 0xffffff;
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
}

// Get map info
void	map_info(t_fdf *fdf, t_map	*map_copy)
{
	z_scale(map_copy->v3d, fdf->map.zscale, fdf->map.n_points);
	if (fdf->map.sphere)
		spherize(fdf, map_copy->v3d);
	x_rot(map_copy->v3d, map_copy->v3d, fdf->map.angle[X], fdf->map.n_points);
	y_rot(map_copy->v3d, map_copy->v3d, fdf->map.angle[Y], fdf->map.n_points);
	z_rot(map_copy->v3d, map_copy->v3d, fdf->map.angle[Z], fdf->map.n_points);
	scale(map_copy->v3d, 30, fdf->map.n_points);
	translate(map_copy->v3d, fdf->map.source, fdf->map.n_points);
	orth_proj(map_copy->v3d, map_copy->v3d, fdf->map.n_points);
}

// Draw map
void	draw_map(t_fdf *fdf)
{
	int	i;
	t_map	*map_copy;

	i = 0;
	map_copy = copy_map(fdf, &fdf->map);
	map_info(fdf, map_copy);
	while (i < fdf->map.n_points)
	{
		// if (map_copy[i].paint)
		// {
			if ((i + 1) % (int)fdf->map.width != 0)
			{
				bresenham(fdf, map_copy->v3d[i], map_copy->v3d[i + 1]);
				// if (meta->map.b_pluslines)
				// {
				// 	if ((i / (int)fdf->map.width) != (fdf->map.height - 1))
				// 		draw_line(fdf, wire[i], wire[i + (int)fdf->map.width + 1]);
				// }
			}
			if ((i / (int)fdf->map.width) != (fdf->map.height - 1))
				bresenham(fdf, map_copy->v3d[i], map_copy->v3d[i + (int)fdf->map.width]);
		// }
		i++;
	}
	mlx_put_image_to_window(fdf->win_ptr, fdf->win_ptr, fdf->mlxdata->img, 0, 0);
}

