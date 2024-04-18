/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:51:27 by marvin            #+#    #+#             */
/*   Updated: 2023/02/07 14:16:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include "lib/libft/inc/libft.h"
# include "lib/minilibx_2019/mlx.h"

# define X 0
# define Y 1
# define Z 2

# define LAT 0
# define LONG 1

# define MAX(a, b) (a > b ? a : b)
# define MOD(a) (a < 0 ? -a : a)


typedef struct s_color
{
	int	max;
	int	mid;
	int	min;
	int	bg;
}		t_color;
typedef struct s_v3d
{
	float	coord[3];
	float	polar[2];
	bool	paint;
	int		color;
	bool	max;
	bool	mid;
	bool	min;
}			t_v3d;
typedef struct s_map
{
	t_v3d	*v3d;
	t_v3d	v;
	t_v3d	source;
	int		**matrix;
	int		min;
	int		max;
	float	width;
	float	height;
	int		n_points;
	int		winx;
	int		winy;
	int		color;
	float	proportion;
	float	angle[3];
	float	zscale;
	float	scale;
	float	curve;
	float	radius;
	float	bend;
	bool	sphere;
	bool	iso;
	bool	parallel;
	bool	diagonals;
}			t_map;
typedef struct s_mlxdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_mlxdata;
typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_mlxdata	*mlxdata;
	t_color		color;
}				t_fdf;

// Process input
void	arg_handler(int ac, char **av);
void	read_file(t_fdf	*fdf, char *filename);
void	matrix_to_v3d(t_fdf *fdf, t_v3d *points);
void	cartesian_to_polar(t_fdf *fdf);
int		map_points(t_map *map);

// Initialise System
void	set_default(t_fdf *fdf, t_map *map);
void	set_colors(t_fdf *fdf, t_v3d *v3d, t_color color);
void	set_extremes(t_fdf *fdf, t_v3d *v3d);
float	min_alt(t_fdf *fdf, t_v3d *v3d);
float	max_alt(t_fdf *fdf, t_v3d *v3d);
void	init_colors(t_fdf *fdf);
void	map_init(t_map *map);

// Colors
int		gradient(int startcolor, int endcolor, int len, int pix);
void	colorize(t_fdf *fdf);

// Draw
void	draw(t_fdf *fdf);
void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
void	draw_line(t_fdf *fdf, t_v3d p, t_v3d p1);
void	wired(t_fdf *fdf);
void	draw_map(t_fdf *fdf);
void	copy_vec(t_fdf *fdf, t_v3d *v3d, t_v3d *copy);
void	opaque(t_v3d *v3d, int len);

// Draw Utils
void	clear_image(t_fdf *fdf);
void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
int		ft_round(float f);

// Matrix Uitls
void	init_matrix(float (*matrix)[3]);

// Projections + transformations
void	scale(t_v3d *v3d, int scale, int len);
void	z_scale(t_v3d *v3d, float scalar, int len);
void	translate(t_v3d *v3d, t_v3d v, int len);
void	x_rot(t_v3d *vectors, t_v3d *projection, int angle, int len);
void	y_rot(t_v3d *vectors, t_v3d *projection, int angle, int len);
void	z_rot(t_v3d *vectors, t_v3d *projection, int angle, int len);
void	orth_proj(t_v3d *v3d, t_v3d *projection, int len);
void	isometric(t_map *map);
void	spherize(t_fdf *fdf, t_v3d *v3d);
void	bend(t_v3d *v3d, int len, float range);
void	parallel(t_map *map);

// Matrix Algebra
t_v3d	mult_mat(t_v3d	v3d, float matrix[3][3]);

// Free
void	dbl_free(char **split);

// Event Handling
int		keypress(int key, void *param);
void	angle(float *angle, float value);
void	angle_ctl(t_fdf *fdf, int key);
void	zoom(t_fdf *fdf, int key);
void	bend_ctl(t_fdf *fdf, int key);
void	color_scheme(t_fdf *fdf, t_color *color, int key);



#endif