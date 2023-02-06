/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:15:07 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/06 13:16:39 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

// Absolute value
float	ft_abs(float f)
{
	if (f < 0)
		f = -f;
	else
		f = f;
	return (f);
}

// Round to nearest integer
int	ft_round(float f)
{
	if (ft_abs(f - (int)f) >= 0.5)
	{
		if (f >= 0)
			f = (int)f + 1;
		else
			f = (int)f - 1;
	}
	else
		f = (int)f;
	return (f);
}

// int main()
// {
// 	float f = 0;
// 	printf("%d\n", ft_round(f));
// 	printf("%f\n", round(f));
// }