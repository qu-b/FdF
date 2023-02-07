/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:39:55 by fcullen           #+#    #+#             */
/*   Updated: 2023/02/07 14:01:03 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <errno.h>

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
void	arg_handler(int ac, char **av)
{
	int	len;
	int	i;
	int	fd;

	len = ft_strlen(av[1]);
	i = 0;
	if (ac != 2)
	{
		ft_printf("Error: Wrong number of arguments\n");
		exit (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 1)
	{
		ft_printf("Error: %s\n", strerror(errno));
		exit (0);
	}
	return ;
}

