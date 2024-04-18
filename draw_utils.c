/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:00:10 by marvin            #+#    #+#             */
/*   Updated: 2023/02/06 08:45:33 by marvin           ###   ########.fr       */
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

// This functions makes the sphere opaque
void	opaque(t_v3d *v3d, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (v3d[i].coord[Z] < 0)
			v3d[i].paint = 0;
		else
			v3d[i].paint = 1;
		i++;
	}
}
