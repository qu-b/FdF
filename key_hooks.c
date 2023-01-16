/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:06:16 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/13 17:10:02 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	angle_control(key, fdf);

	return (0);
}

int	key_release(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (key == 259)
		fdf->keys.b_keyctrl = 0;
	return (0);
}
