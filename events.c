#include "fdf.h"

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
