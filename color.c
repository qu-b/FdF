/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:33:38 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/08 11:40:55 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Initialise Base Colors
void	init_colors(t_fdf *fdf)
{
	fdf->color.bg = 0x000000;
	fdf->color.max = 0xffffff;
	fdf->color.mid = 0x1b7e48;
	fdf->color.min = 0x3d54c8;
}

// Round to nearest integer
int	ft_round(float f)
{
	if (fabsf(f - (int)f) >= 0.5)
	{
		if (f >= 0)
			f = (int)f + 1;
		else
			f = (int)f - 1;
	}
	else
		f = (int)f;
	return (f);
}

// Color gradient algorithm
int	gradient(int startcolor, int endcolor, int len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((endcolor >> 16) - \
					(startcolor >> 16)) / (double)len;
	increment[1] = (double)(((endcolor >> 8) & 0xFF) - \
					((startcolor >> 8) & 0xFF)) / (double)len;
	increment[2] = (double)((endcolor & 0xFF) - (startcolor & 0xFF)) \
					/ (double)len;
	new[0] = (startcolor >> 16) + ft_round(pix * increment[0]);
	new[1] = ((startcolor >> 8) & 0xFF) + ft_round(pix * increment[1]);
	new[2] = (startcolor & 0xFF) + ft_round(pix * increment[2]);
	newcolor = (new[0] << 16) + (new[1] << 8) + new[2];
	return (newcolor);
}

// Set colors for each point
void	set_colors(t_fdf *fdf, t_v3d *v3d, t_color color)
{
	v3d->paint = 1;
	if (v3d->max == 1)
		v3d->color = color.max;
	else if (v3d->min == 1)
		v3d->color = color.min;
	else if (v3d->mid == 1)
		v3d->color = color.mid;
	else if (v3d->coord[Z] > 0)
		v3d->color = gradient(color.mid, color.max,
				fdf->map.max, v3d->coord[Z]);
	else
		v3d->color = gradient(color.min, color.mid,
				-fdf->map.min, v3d->coord[Z]);
}

// Colorize each pixel
void	colorize(t_fdf *fdf)
{
	int		i;

	i = 0;
	while (i < fdf->map.n_points)
	{
		set_colors(fdf, &fdf->map.v3d[i], fdf->color);
		i++;
	}
}
