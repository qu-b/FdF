/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:51:06 by marvin            #+#    #+#             */
/*   Updated: 2023/02/07 17:35:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	destroy(t_fdf *fdf)
{
	free(fdf);
	exit (0);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	arg_handler(ac, av);
	fdf = malloc(sizeof(*fdf));
	if (!fdf)
		return (0);
	read_file(fdf, av[1]);
	if (fdf->map.width == 0 || fdf->map.height == 0)
		return (1);
	draw_map(fdf);
	mlx_hook(fdf->win_ptr, 2, 1L << 0, keypress, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, destroy, fdf);
	mlx_put_image_to_window(fdf->win_ptr,
		fdf->win_ptr, fdf->mlxdata->img, 0, 0);
	mlx_loop(fdf->mlx_ptr);
	free(fdf);
	return (0);
}
