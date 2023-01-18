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
	draw(fdf);
	return (0);
}
