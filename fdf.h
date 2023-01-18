/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:51:27 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/13 19:27:37 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "lib/libft/inc/libft.h"
# include "lib/minilibx_2019/mlx.h"


typedef struct	s_mlxdata 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_mlxdata;

typedef struct s_map
{
	int		width;
	int		height;
	int		**matrix;
}			t_map;

typedef struct s_graphics
{
	int		color;
	int		scale;
	int		z_scale;
	int		is_iso;
	double	angle;
	int		win_x;
	int		win_y;
	int		zoom;
	int		shift_x;
	int		shift_y ;
}			t_graphics;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_graphics	*graphics;
	t_mlxdata	*mlxdata;
}				t_fdf;

// Process input
void	read_file(t_fdf	*fdf, char *filename);

// Draw
void	bresenham(t_fdf *fdf, float x, float y, float x1, float y1);
void	draw(t_fdf *fdf);
void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);


// Utils
void	dbl_free(char **split);

#endif