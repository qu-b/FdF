#include "fdf.h"

int	keypress(int key, t_fdf *fdf, void *param)
{

	(void) param;
	printf("%d\n ", key);
	clear_image(fdf);
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit (0);
	}
	// if (key == 126)
	// 	fdf->map->shift_y -= 10;
	// if (key == 125)
	// 	fdf->map->shift_y += 10;
	// if (key == 124)
	// 	fdf->map->shift_x += 10;
	// if (key == 123)
	// 	fdf->map->shift_x -= 10;
	// if (key == 24)
	// 	fdf->map->zoom += 0.2;
	// if (key == 27)
	// 	fdf->map->zoom -= 0.2;
	// if (key == 33)
	// 	fdf->map->angle_a -= 0.05;
	// if (key == 30)
	// 	fdf->map->angle_a += 0.05;
	// if (key == 41)
	// 	fdf->map->angle_b -= 0.05;
	// if (key == 39)
	// 	fdf->map->angle_b += 0.05;
	// if (key == 43)
	// 	fdf->map->z_zoom -= 0.1;
	// if (key == 47)
	// 	fdf->map->z_zoom += 0.1;
	// if (key == 34)
		// fdf->map->iso = !fdf->map->iso;
	// if (key == 1)
	// 	fdf->map->sphere = !fdf->map->sphere;
	if (key == 34)
	{
		isometric(&fdf->map);
		draw_map(fdf);
	}
	draw_map(fdf);
	return (0);
}
