/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpluchar <vpluchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:11:37 by vpluchar          #+#    #+#             */
/*   Updated: 2017/10/29 21:09:59 by vpluchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				ft_createmap(int fd, t_wolf *e)
{
	char	**tmp;
	int		i;
	int		j;
	char	*line;

	j = -1;
	i = -1;
	e->map = (int **)malloc(sizeof(int *) * e->ymax);
	while (++i < e->ymax)
	{
		if (ft_gnl(fd, &line) < 0)
			return (-1);
		tmp = ft_strsplit(line, ' ');
		free(line);
		e->map[i] = (int *)malloc(sizeof(int) * e->xmax);
		while (++j < e->xmax)
		{
			e->map[i][j] = ft_atoi(tmp[j]);
			free(tmp[j]);
		}
		free(tmp);
		j = -1;
	}
	return (1);
}

int				ft_check(int fd, t_wolf *e)
{
	char	*line;
	int		i;
	char	c;

	e->xmax = 0;
	e->ymax = 0;
	while ((c = ft_gnl(fd, &line)) > 0)
	{
		if (!e->xmax)
			e->xmax = ft_countwords(line, ' ');
		if (ft_countwords(line, ' ') == e->xmax)
		{
			i = -1;
			while (line[++i])
				if (!ft_strchr(" 0123456789", line[i]))
					return (-1);
			e->ymax++;
		}
		else
			return (-1);
		ft_strdel(&line);
	}
	if (c == 0 && e->xmax && e->ymax)
		return (1);
	return (-1);
}

int		open_map(char *map, t_wolf *e)
{
	int	fd;

	if (!(fd = open(map, O_RDONLY)))
		return (2);
	if (ft_check(fd, e) < 0)
		return (4);
	close(fd);
	if (!(fd = open(map, O_RDONLY)))
		return (2);
	if (!(ft_createmap(fd, e)))
		return (5);
	close(fd);
	return(0);
}
