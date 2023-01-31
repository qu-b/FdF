/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 09:47:00 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/31 16:53:31 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Initialise necessary mlx values
void	mlxdata_init(t_fdf *fdf)
{
	t_mlxdata	*mlxdata;

	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1080, 720, "FDF");
	fdf->mlxdata = malloc(sizeof(*mlxdata));
	if (!fdf->mlxdata)
		return ;
	fdf->mlxdata->img = mlx_new_image(fdf->mlx_ptr, 1080, 720);
	fdf->mlxdata->addr = mlx_get_data_addr(fdf->mlxdata->img,
			&fdf->mlxdata->bits_per_pixel, &fdf->mlxdata->line_length,
			&fdf->mlxdata->endian);
}

// Initialise map with default settings
void	map_init(t_map *map)
{
	map->scale = 50;
	map->zscale = 20;
	map->winx = 1080;
	map->winy = 720;
	map->lines = 1;
	map->sphere = 0;
	map->iso = 0;
	map->bend = 0;
	map->source.coord[X] = 1080 / 2;
	map->source.coord[Y] = 720 / 2;
	map->source.coord[Z] = 0;
	map->angle[X] = 0;
	map->angle[Y] = 0;
	map->angle[Z] = 0;
}

// Wrapper initialisation function
void	set_default(t_fdf *fdf, t_map *map)
{
	map_init(map);
	mlxdata_init(fdf);
}
