/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:39:45 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/08 11:58:18 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Control Color Scheme 2
void	color_scheme_2(t_fdf *fdf, t_color *color, int key)
{
	if (key == 20)
	{
		color->bg = 0x000000;
		color->mid = 0x9e0059;
		color->max = 0xffbd00;
		color->min = 0x390099;
	}
	if (key == 21)
	{
		color->bg = 0x000000;
		color->max = 0xb7094c;
		color->mid = 0x5c4d7d;
		color->min = 0x0091ad;
	}
	colorize(fdf);
}

// Control Color Scheme
void	color_scheme(t_fdf *fdf, t_color *color, int key)
{
	if (key == 18)
	{
		color->bg = 0x000000;
		color->max = 0xffffff;
		color->mid = 0x1b7e48;
		color->min = 0x3d54c8;
	}
	if (key == 19)
	{
		color->bg = 0x000000;
		color->max = 0xffffff;
		color->mid = 0xced4da;
		color->min = 0x343a40;
	}
	color_scheme_2(fdf, color, key);
}
