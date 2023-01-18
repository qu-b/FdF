/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:51:06 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/13 20:31:48 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_default(t_fdf *fdf)
{
	t_graphics	*graphics;
	t_mlxdata	*mlxdata;


	// fdf->mlx.mlx_ptr = mlx_init();
	// fdf->mlx.win_ptr = mlx_new_window(fdf->mlx.mlx_ptr, 
							// fdf->graphics.win_x, fdf->graphics.win_y, "FDF");
	fdf->mlxdata = malloc(sizeof(*mlxdata));
	fdf->mlxdata->img = mlx_new_image(fdf->mlx_ptr, 1920, 1080);
	fdf->mlxdata->addr = mlx_get_data_addr(fdf->mlxdata->img, &fdf->mlxdata->bits_per_pixel,
							&fdf->mlxdata->line_length, &fdf->mlxdata->endian);
	fdf->graphics = malloc(sizeof(*graphics));
	fdf->graphics->scale = 20;
	fdf->graphics->zoom = 20;
	// fdf->graphics->z_scale = 1;
	fdf->graphics->is_iso = 1;
	fdf->graphics->bg_color = 000000;
	fdf->graphics->angle_a = 0.8;
	fdf->graphics->angle_b = 0.8;
	fdf->graphics->z_zoom = 1;
	fdf->graphics->win_x = 1000;
	fdf->graphics->win_y = 1000;
	fdf->graphics->shift_x = fdf->graphics->win_x / 3;
	fdf->graphics->shift_y = fdf->graphics->win_y / 3;
}

int		destroy(t_fdf *fdf)
{
	free(fdf);
	exit (1);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	(void)ac;
	fdf = malloc((sizeof(*fdf)));
	read_file(fdf, av[1]);
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1000, 1000, "FDF");
	set_default(fdf);
	draw(fdf);
	mlx_hook(fdf->win_ptr, 2, 1L << 0, keypress, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, destroy, fdf);
	mlx_put_image_to_window(fdf->win_ptr, fdf->win_ptr, fdf->mlxdata->img, 0, 0);
	mlx_loop(fdf->mlx_ptr);
	free(fdf);
	return (0);
}
