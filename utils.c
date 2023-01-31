/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:39:55 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/30 17:04:53 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Double free for arrays of char array
void	dbl_free(char **split)
{
	int	i;

	if (!split)
		return ;
	i = -1;
	while (split[++i])
		free (split[i]);
	free (split);
}

// Argument Handler
void	arg_handler(int ac, char **av, char **env)
{
	int	len;
	int	i;

	len = ft_strlen(av[1]);
	i = 0;
	if (ac != 2)
	{
		ft_printf("Wrong number of arguments...\n");
		exit (0); // Can you use exit()?
	}
	while (env[i] && ft_strncmp(av[1], *env, len))
		i++;
	printf("%s\n", env[++i]);
	// if (!env[i])
	// {
	// 	ft_printf("Can't find the map in the given path...\n");
	// 	exit(0);
	// }
	return ;
}

// // Copy map with all settings
// t_map	copy_map(t_fdf *fdf, t_map map)
// {
// 	t_map copy;

// 	copy = malloc(sizeof(t_map));
// 	if (!copy)
// 		return (0);
// 	copy.v3d = copy_vec(fdf, map.v3d);
// 	copy = map;
// 	return (copy);
// }

// Copy all map vectors to a new 3D vector array
void	copy_vec(t_fdf *fdf, t_v3d *v3d, t_v3d *copy)
{
	int	i;

	i = 0;
	while (i < fdf->map.n_points)
	{
		copy[i] = v3d[i];
		i++;
	}

}

// Find maximum altitude
float	max_alt(t_fdf *fdf, t_v3d *v3d)
{
	int		i;
	float	max;

	i = 0;
	max = 0;
	while (i < fdf->map.n_points)
	{
		if (v3d[i].coord[Z] > max)
			max = v3d[i].coord[Z];
		i++;
	}
	return (max);
}

// Find minimum altitude
float	min_alt(t_fdf *fdf, t_v3d *v3d)
{
	int		i;
	float	min;

	i = 0;
	min = 0;
	while (i < fdf->map.n_points)
	{
		if (v3d[i].coord[Z] < min)
			min = v3d[i].coord[Z];
		i++;
	}
	return (min);
}

// Set extremes for each vector
void	set_extremes(t_fdf *fdf, t_v3d *v3d)
{
	int		i;

	fdf->map.max = max_alt(fdf, fdf->map.v3d);
	fdf->map.min = min_alt(fdf, fdf->map.v3d);
	i = 0;
	while (i < fdf->map.n_points)
	{
		if (v3d[i].coord[Z] == fdf->map.max)
			v3d[i].max = true;
		else if (v3d[i].mid == true)
			v3d[i].mid = true;
		else if (v3d[i].coord[Z] == fdf->map.min)
			v3d[i].min = true;
		i++;
	}
}

// Initialise Colors
void	init_colors(t_fdf *fdf)
{
	fdf->color.bg = 0x000000; // black
	fdf->color.max = 0x1b7e48; // green
	fdf->color.mid = 0xffffff; // white
	fdf->color.min = 0x3d54c8; // blue

}
// Set colors for each point
void	set_colors(t_fdf *fdf, t_v3d *v3d, t_color color)
{
	int		i;

	i = 0;
	while (i < fdf->map.n_points)
	{
		if (v3d[i].max == true)
			v3d[i].color = color.max;
		else if (v3d[i].mid == true)
			v3d[i].color = color.mid;
		else if (v3d[i].min == true)
			v3d[i].color = color.min;
		i++;
	}
}