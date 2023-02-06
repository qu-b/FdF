/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:32:53 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/06 13:10:30 by fcullen          ###   ########.fr       */
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
		angle(&fdf->map.angle[Z], -1);
	if (key == 47)
		angle(&fdf->map.angle[Z], 1);
	if (key == 123)
		angle(&fdf->map.angle[Y], -1);
	if (key == 124)
		angle(&fdf->map.angle[Y], 1);
	if (key == 125)
		angle(&fdf->map.angle[X], -1);
	if (key == 126)
		angle(&fdf->map.angle[X], 1);
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
void	bend_ctl(t_fdf *fdf, int key)
{
	if (key == 11)
		fdf->map.bend += 0.0001;
	if (key == 9)
		fdf->map.bend -= 0.0001;
}
