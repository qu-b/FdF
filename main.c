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

	fdf->graphics = malloc(sizeof(*graphics));
	fdf->graphics->scale = 20;
	fdf->graphics->z_scale = 1;
	fdf->graphics->is_iso = 1;
	fdf->graphics->angle = 0.523599;
	fdf->graphics->win_x = 1000;
	fdf->graphics->win_y = 1000;
	fdf->graphics->shift_x = fdf->graphics->win_x / 3;
	fdf->graphics->shift_y = fdf->graphics->win_y / 3;
	// fdf->mlx.mlx_ptr = mlx_init();
	// fdf->mlx.win_ptr =\
	// mlx_new_window(fdf->mlx.mlx_ptr, fdf->graphics.win_x, fdf->graphics.win_y, "FDF");
}

int	deal_key(int key, t_fdf *fdf, void *param)
{

	(void) param;
	printf("%d\n ", key);
	// fdf->graphics->shift_x = key;
	// if (key == 126)
	// 	fdf->graphics->shift_y -= 10;
	// if (key == 125)
	// 	fdf->graphics->shift_y += 10;
	// if (key == 124)
	// 	fdf->graphics->shift_x += 10;
	// if (key == 123)
	// 	fdf->graphics->shift_x -= 10;
	// mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	draw(fdf);
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	(void)ac;
	fdf = malloc((sizeof(*fdf)));
	read_file(fdf, av[1]);
	// for (int i = 0; i < fdf->map.height; i++)
	// {
	// 	for (int j = 0; j < fdf->map.width; j++)
	// 	{
	// 		if (j < fdf->map.width - 1)
	// 			printf("%d ", fdf->map.matrix[i][j]);
	// 		else
	// 			printf("%d", fdf->map.matrix[i][j]);
	// 	}
	// 	printf("\n");
	// }
	set_default(fdf);
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1000, 1000, "FDF");
	fdf->graphics->zoom = 20;
	fdf->graphics->shift_x = 150;
	fdf->graphics->shift_y = 150;
	// bresenham(fdf, 10, 10, 5, 5);
	draw(fdf);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	// mlx_key_hook(fdf->win_ptr, deal_key, NULL);
	mlx_loop(fdf->mlx_ptr);
	free(fdf);
	return (0);
}
