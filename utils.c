/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:39:55 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/13 13:42:25 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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