#include "wolf.h"

static void ft_putpx(t_wolf *e, int x, int y, unsigned int c)
{
	int i;
	int *tmp;
	tmp = (int *)e->data;
	i = x + (y * WID);
	tmp[i] = c;
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
	if (((e->rx < 0 && e->ry < 0) || (e->rx >= 0 && e->ry < 0)) && e->side)
		e->color = COLORA;
	else if (((e->rx < 0 && e->ry >= 0) || (e->rx >= 0 && e->ry >= 0)) && e->side)
		e->color = COLORB;
	else if (((e->rx < 0 && e->ry < 0) || (e->rx >= 0 && e->ry >= 0)) && !e->side)
		e->color = COLORC;
	else
		e->color = COLORD;
	return (ft_drawline(e, sl, el, i));
}

static void ft_dist(t_wolf *e)
{
	while (!e->dist)
	{
		if (e->sx < e->sy)
		{
			e->sx += e->rdx;
			e->mx += (e->rx < 0) ? -1 : 1;
			e->side = 0;
		}
		else 
		{
			e->sy += e->rdy;
			e->my += (e->ry < 0) ? -1 : 1;
			e->side = 1;
		}
		if (e->map[e->mx][e->my])
		{
			if (e->side)
				e->dist = (e->my - e->y + (1 - ((e->ry < 0) ? -1 : 1)) / 2) / e->ry;
			else
				e->dist = (e->mx - e->x + (1 - ((e->rx < 0) ? -1 : 1)) / 2) / e->rx;
		}
	}
}

int			 ft_raycast(t_wolf *e)
{
	int x;

	x = -1;
	while (++x < WID)
	{
	e->mx = (int)e->x;
	e->my = (int)e->y;
		e->rcam = 2 * x / (double)WID - 1;
		e->rx = e->dx + e->px * e->rcam;
		e->ry = e->dy + e->py * e->rcam;
		e->rdx = sqrt(1 + (e->ry * e->ry) / (e->rx * e->rx));
		e->rdy = sqrt(1 + (e->rx * e->rx) / (e->ry * e->ry));
		e->sx = ((e->rx < 0) ? (e->x - e->mx) : (e->mx - e->x)) * e->rdx;
		e->sy = ((e->ry < 0) ? (e->y - e->my) : (e->my - e->y)) * e->rdy;
		e->side = -1;
		e->dist = 0;
		ft_dist(e);
		ft_rdraw(e, x);
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	ft_bzero(e->data, WID * HEI * e->bpp);
	return (0);
}
