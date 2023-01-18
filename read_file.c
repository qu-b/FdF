/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:44:58 by fcullen           #+#    #+#             */
/*   Updated: 2023/01/13 16:01:03 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *filename)
{
	int		fd;
	int		height;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	while (get_next_line(fd))
		height++;
	close(fd);
	return (height);
}

int	get_width(char *filename)
{
	int		fd;
	int		i;
	int		width;
	char	*line;
	char	**split;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	width = 0;
	line = get_next_line(fd);
	i = ft_strlen(line);
	if (line[--i] == '\n')
		line[i] = '\0';
	split = ft_split(line, ' ');
	while (split[width])
		width++;
	close(fd);
	free(line);
	return (width);
}

void	populate_matrix(t_fdf *fdf, int fd)
{
	char	**split;
	char	*line;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (j < fdf->map.height)
	{
		line = get_next_line(fd);
		printf("%s ", line);
		k = ft_strlen(line);
		if (line[--k] == '\n')
			line[k] = '\0';
		split = ft_split(line, ' ');
		fdf->map.matrix[j] = malloc(sizeof(int) * fdf->map.width);
		while (split[i] != 0)
		{
			printf("%s ", split[i]);
			fdf->map.matrix[j][i] = ft_atoi(split[i]);
			i++;
		}
		printf("\n");
		i = 0;
		j++;
		dbl_free (split);
	}
}

int	**get_matrix(t_fdf *fdf, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	fdf->map.matrix = malloc(sizeof(int *) * fdf->map.height);
	populate_matrix(fdf, fd);
	close(fd);
	return (fdf->map.matrix);
}

void	read_file(t_fdf	*fdf, char *filename)
{
	fdf->map.width = get_width(filename);
	fdf->map.height = get_height(filename);
	fdf->map.matrix = get_matrix(fdf, filename);
}
