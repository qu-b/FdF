/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:39:42 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/03 18:08:57 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Handles Key Presses
int	keypress(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	printf("%d\n ", key);
	clear_image(fdf);
	angle_ctl(fdf, key);
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit (0);
	}
	zoom(fdf, key);
	bend_ctl(fdf, key, fdf->map.v3d);
	if (key == 15)
		map_init(&fdf->map);
	if (key == 35)
	{
		parallel(&fdf->map);
		draw_map(fdf);
	}
	if (key == 33)
		if (fdf->map.zscale != 0)
			fdf->map.zscale += 1;
	if (key == 30)
		fdf->map.zscale -= 1;
	if (key == 1)
		fdf->map.sphere = !fdf->map.sphere;
	if (key == 34)
	{
		isometric(&fdf->map);
	}
	color_scheme(fdf, &fdf->color, key);
	draw_map(fdf);
	return (0);
}
