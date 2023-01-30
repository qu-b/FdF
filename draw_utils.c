/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:00:10 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/27 17:26:02 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// This is a better version of the mlx_pixel_put function.

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= fdf->map.winx
		|| y < 0 || y >= fdf->map.winy)
		return ;
	dst = fdf->mlxdata->addr + (y * fdf->mlxdata->line_length
			+ x * (fdf->mlxdata->bits_per_pixel / 8));
	*(unsigned int *) dst = color ;
}

// This function is used to clear the background before
// drawing another image.

void	clear_image(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.winx)
	{
		j = 0;
		while (j < fdf->map.winy)
		{
			my_mlx_pixel_put(fdf, i, j, fdf->color.bg);
			j++;
		}
		i++;
	}
}
