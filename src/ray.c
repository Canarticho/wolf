#include "wolf.h"

static void ft_putpx(t_wolf *e, int x, int y, unsigned int c)
{
	int i;
	int *tmp;
	tmp = (int *)e->data;
	i = x + (y * WID);
	tmp[i++] = c;
	tmp[i++] = c >> 8;
	tmp[i] = c >> 16;
}

static void ft_drawline(t_wolf *e, int sl ,int el, int x)
{
	int i;

	i = -1;
	while (++i < sl)
		ft_putpx(e, x, i, COLORS);
	i--;
	while (++i >= sl && i < el)
		ft_putpx(e, x, i, e->color);
	i--;
	while (++i < sl)
		ft_putpx(e, x, i, COLORG);
}

static void ft_rdraw(t_wolf *e, int i)
{
	int hei;
	int sl;
	int el;

	hei = (int)(HEI / e->dist);
	sl = -hei / 2 + HEI / 2;
	if (sl < 0)
		sl = 0;
	el = hei / 2 + HEI / 2;
	if (el >= HEI)
		el = HEI - 1;
	if (((e->sx > 0 && e->sy > 0) || (e->sx < 0 && e->sy > 0)) && e->side)
		e->color = COLORA;
	if (((e->sx > 0 && e->sy < 0) || (e->sx < 0 && e->sy < 0)) && e->side)
		e->color = COLORB;
	if (((e->sx > 0 && e->sy > 0) || (e->sx < 0 && e->sy > 0)) && !e->side)
		e->color = COLORC;
	else
		e->color = COLORD;
	return (ft_drawline(e, sl, el, i));
}

static void ft_dist(t_wolf *e)
{
	while (!e->hit)
	{
		if (e->sx < e->sx)
		{
			e->sx += e->rdx;
			e->mx += (e->sx > 0) ? (1) : (-1);
			e->side = 0;
		}
		else 
		{
			e->sy += e->rdy;
			e->my += (e->sy > 0) ? (1) : (-1);
			e->side = 1;
		}
		if (e->map[e->mx][e->my])
		{
			e->hit = 1;
			if (e->side)
				e->dist = (e->my - e->y + (1 - e->sy) / 2) / e->ry;
			else
				e->dist = (e->mx - e->x + (1 - e->sx) / 2) / e->rx;
		}
	}
}

int			 ft_raycast(t_wolf *e)
{
	int x;

	x = -1;
	e->mx = (int)e->x;
	e->my = (int)e->y;
	e->rx = e->dx + e->px * e->rcam;
	e->ry = e->dy + e->py * e->rcam;
	e->dx = sqrt(1 + (e->dy * e->dy) / (e->dx * e->dx));
	e->dx = sqrt(1 + (e->dx * e->dx) / (e->dy * e->dy));
	e->sx = ((e->rx < 0) ? (e->x - (int)e->x) : ((int)e->x - e->x)) * e->rdx;
	e->sy = ((e->ry < 0) ? (e->y - (int)e->y) : ((int)e->y - e->y)) * e->rdy;
	e->hit = 0;
	while (++x < WID)
	{
		e->rcam = 2 * x / WID - 1;
		ft_dist(e);
		ft_rdraw(e, x);
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}
