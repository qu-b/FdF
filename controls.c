/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:32:53 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/03 18:22:34 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Apply angle change for rotation
void	angle(float *angle, float value)
{
	*angle += value;
	if (*angle < 0)
		*angle += 360;
	if (*angle >= value)
		*angle -= 360;
}

// Angle Control
void	angle_ctl(t_fdf *fdf, int key)
{
	if (key == 43)
		angle(&fdf->map.angle[Z], -10);
	if (key == 47)
		angle(&fdf->map.angle[Z], 10);
	if (key == 123)
		angle(&fdf->map.angle[Y], -10);
	if (key == 124)
		angle(&fdf->map.angle[Y], 10);
	if (key == 125)
		angle(&fdf->map.angle[X], -10);
	if (key == 126)
		angle(&fdf->map.angle[X], 10);
}

// Zoom control
void	zoom(t_fdf *fdf, int key)
{
	if (key == 27)
		fdf->map.scale /= 1.25;
	if (key == 24)
		fdf->map.scale *= 1.25;
}

// Bend control
void	bend_ctl(t_fdf *fdf, int key, t_v3d *v3d)
{
	if (key == 11)
		bend(v3d, fdf->map.n_points, fdf->map.bend);
}

// Control Color Scheme
void	color_scheme(t_fdf *fdf, t_color *color, int key)
{
	if (key == 18)
	{
		color->bg = 0x000000;
		color->max = 0x1b7e48;
		color->mid = 0x3d54c8;
		color->min = 0x3d54c8;
	}
	if (key == 19)
	{
		color->bg = 0x000000;
		color->max = 0xffffff;
		color->min = 0xffffff;
	}
	if (key == 20)
	{
		color->bg = 0x000000;
		color->max = 0x000000;
		color->min = 0x000000;
	}
	if (key == 21)
	{
		color->bg = 0x000000;
		color->max = 0xb7094c;
		color->mid = 0x5c4d7d;
		color->min = 0x0091ad;
	}
	colorize(fdf);
}
