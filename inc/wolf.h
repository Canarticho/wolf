/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpluchar <vpluchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:14:46 by vpluchar          #+#    #+#             */
/*   Updated: 2017/11/01 00:29:56 by chle-van         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "mlx.h"
# include "libft.h"
# include <math.h>

# define WID 1280
# define HEI 800
# define ESC 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define TS 0.05
# define MS 0.05

# define COLORA 0Xcc43fe
# define COLORB 0X42e5fe
# define COLORC 0Xdffe42
# define COLORD 0X42fea0
# define COLORS 0Xffffff
# define COLORG 0Xfe4242

typedef struct	s_wolf
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			**map;
	int			xmax;
	int			ymax;
	int			sline;
	int			bpp;
	int			endian;
	int			hit;
	int			side;
	int			mx;
	int			my;
	int			color;
	double		ts;
	double		ms;
	double		tmp;
	double		dist;
	double		x;
	double		y;
	double		dx;
	double		dy;
	double		px;
	double		py;
	double		rx;
	double		ry;
	double		rdx;
	double		rdy;
	double		sx;
	double		sy;
	double		rcam;

}				t_wolf;

int				ft_exit(t_wolf *e);
int				ft_move(int key, t_wolf *e);
int				open_map(char *map, t_wolf *e);
int				ft_raycast(t_wolf *e);
#endif
