/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:23:02 by marvin            #+#    #+#             */
/*   Updated: 2023/02/06 14:00:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Scale z-axis to modify altitude
void	z_scale(t_v3d *v3d, float scalar, int len)
{
	int	i;

	i = 0;
	if (scalar != 0)
	{
		while (i < len)
		{
			v3d[i].coord[Z] /= scalar;
			i++;
		}
	}
}

// Bend
void	bend(t_v3d *v3d, int len, float range)
{
	int		i;
	float	bend;

	i = 0;
	while (i < len)
	{
		bend = ((v3d[i].coord[X] * v3d[i].coord[X]) * (range))
			+ (v3d[i].coord[Y] * v3d[i].coord[Y]) * (range);
		v3d[i].coord[Z] -= bend;
		i++;
	}
}
