/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:32:53 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/31 16:46:04 by fcullen          ###   ########.fr       */
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