/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:24:27 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/06 16:17:32 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Copy all map vectors to a new 3D vector array
void	copy_vec(t_fdf *fdf, t_v3d *v3d, t_v3d *copy)
{
	int	i;

	i = 0;
	while (i < fdf->map.n_points)
	{
		copy[i] = v3d[i];
		copy[i].color = v3d[i].color;
		i++;
	}
}

// Find maximum altitude
float	max_alt(t_fdf *fdf, t_v3d *v3d)
{
	int		i;
	float	max;

	i = 0;
	max = 0;
	while (i < fdf->map.n_points)
	{
		if (v3d[i].coord[Z] > max)
			max = v3d[i].coord[Z];
		i++;
	}
	return (max);
}

// Find minimum altitude
float	min_alt(t_fdf *fdf, t_v3d *v3d)
{
	int		i;
	float	min;

	i = 0;
	min = 0;
	while (i < fdf->map.n_points)
	{
		if (v3d[i].coord[Z] < min)
			min = v3d[i].coord[Z];
		i++;
	}
	return (min);
}

// Set extremes for each vector
void	set_extremes(t_fdf *fdf, t_v3d *v3d)
{
	int		i;

	fdf->map.max = max_alt(fdf, fdf->map.v3d);
	fdf->map.min = min_alt(fdf, fdf->map.v3d);
	i = 0;
	while (i < fdf->map.n_points)
	{
		if (v3d[i].coord[Z] == fdf->map.max)
			v3d[i].max = 1;
		else if (v3d[i].coord[Z] == fdf->map.min)
			v3d[i].min = 1;
		i++;
	}
}
