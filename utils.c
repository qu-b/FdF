/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:39:55 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/06 19:01:03 by fcullen          ###   ########.fr       */
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
		exit (0);
	}
	printf("%s\n", av[1]);
	while (ft_strncmp("PWD=", *env, 4))
		env++;
	// while (ft_strncmp(av[1], *env, len))
	// 	env++;
	printf("%s\n", *env);
	// if (!env[i])
	// {
	// 	ft_printf("Can't find the map in the given path...\n");
	// 	exit(0);
	// }
	return ;
}

