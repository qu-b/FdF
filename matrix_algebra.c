/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_algebra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:25:04 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/26 16:19:50 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Initialise Matrix
void	init_matrix(float (*matrix)[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}
}


// Function to multiply a 3D vector by a 3x3 matrix
t_v3d	mult_mat(t_v3d	v3d, float matrix[3][3])
{
	int		i;
	int		j;
	t_v3d	result;

	i = 0;
	result = v3d;
	while (i < 3)
	{
		j = 0;
		result.coord[i] = 0;
		while (j < 3)
		{
			result.coord[i] += matrix[i][j] * v3d.coord[j];
			j++;
		}
		i++;
	}
	return (result);
}