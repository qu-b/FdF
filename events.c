#include "fdf.h"

int	keypress(int key, t_fdf *fdf, void *param)
{

	(void) param;
	printf("%d\n ", key);
	clear_image(fdf);
	if (key == 53)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr); 
	if (key == 126)
		fdf->graphics->shift_y -= 10;
	if (key == 125)
		fdf->graphics->shift_y += 10;
	if (key == 124)
		fdf->graphics->shift_x += 10;
	if (key == 123)
		fdf->graphics->shift_x -= 10;
	if (key == 24)
		fdf->graphics->zoom += 3;
	if (key == 27)
		fdf->graphics->zoom -= 3;
	if (key == 33)
		fdf->graphics->angle_a -= 0.05;
	if (key == 30)
		fdf->graphics->angle_a += 0.05;
	if (key == 41)
		fdf->graphics->angle_b -= 0.05;
	if (key == 39)
		fdf->graphics->angle_b += 0.05;
	if (key == 43)
		fdf->graphics->z_zoom -= 1;
	if (key == 47)
		fdf->graphics->z_zoom += 1;
	if (key == 34)
		fdf->graphics->iso = !fdf->graphics->iso;
	if (key == 1)
		fdf->graphics->sphere = !fdf->graphics->sphere;
	draw(fdf);
	return (0);
}
