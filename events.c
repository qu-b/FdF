/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:39:42 by marvin            #+#    #+#             */
/*   Updated: 2023/02/07 17:36:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Handles Yet More Key Presses
int	keypress3(int key, t_fdf *fdf)
{
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		free(fdf);
		exit (0);
	}
	if (key == 15)
		map_init(&fdf->map);
	if (key == 35)
	{
		parallel(&fdf->map);
		draw_map(fdf);
	}
	return (0);
}

// Handles More Key Presses
int	keypress2(int key, t_fdf *fdf)
{
	if (key == 0)
		fdf->map.source.coord[X] -= 10;
	if (key == 2)
		fdf->map.source.coord[X] += 10;
	if (key == 1)
		fdf->map.source.coord[Y] += 10;
	if (key == 13)
		fdf->map.source.coord[Y] -= 10;
	if (key == 12)
		fdf->map.source.coord[Z] -= 10;
	if (key == 14)
		fdf->map.source.coord[Z] += 10;
	if (key == 37)
		fdf->map.diagonals = !fdf->map.diagonals;
	return (0);
}

// Handles Key Presses
int	keypress(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	clear_image(fdf);
	angle_ctl(fdf, key);
	zoom(fdf, key);
	bend_ctl(fdf, key);
	keypress2(key, fdf);
	keypress3(key, fdf);
	if (key == 33 && fdf->map.zscale != 0)
			fdf->map.zscale += 1;
	if (key == 30)
		fdf->map.zscale -= 1;
	if (key == 5)
		fdf->map.sphere = !fdf->map.sphere;
	if (key == 34)
		isometric(&fdf->map);
	color_scheme(fdf, &fdf->color, key);
	draw_map(fdf);
	return (0);
}
