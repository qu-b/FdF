/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:51:27 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/20 17:58:53 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "lib/libft/inc/libft.h"
# include "lib/minilibx_2019/mlx.h"

# define X 0
# define Y 1
# define Z 2

# define LAT 0
# define LONG 1
typedef struct	s_mlxdata 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_mlxdata;

typedef struct s_v3d
{
	int		coord[3];
	float	polar[2];
}			t_v3d;

typedef struct s_map
{
	int		width;
	int		height;
	int		**matrix;
	float	radius;
}			t_map;

typedef struct s_graphics
{
	int		color;
	int		bg_color;
	int		scale;
	int		z_scale;
	int		is_iso;
	double	angle_a;
	double	angle_b;
	int		win_x;
	int		win_y;
	int		zoom;
	bool	sphere;
	int		z_zoom;
	int		shift_x;
	int		shift_y ;
}			t_graphics;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_v3d		*v3d;
	t_graphics	*graphics;
	t_mlxdata	*mlxdata;
}				t_fdf;

// Process input
void	read_file(t_fdf	*fdf, char *filename);
t_v3d	*matrix_to_v3d(t_fdf *fdf);
void	cartesian_to_polar(t_fdf *fdf);
int		map_points(t_map map);

// Draw
void	bresenham(t_fdf *fdf, float x, float y, float x1, float y1);
void	draw(t_fdf *fdf);
void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);


// Utils
void	dbl_free(char **split);

// Event Handling
int		keypress(int key, t_fdf *fdf, void *param);
void	clear_image(t_fdf *fdf);


#endif