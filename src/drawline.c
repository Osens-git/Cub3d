/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:24:05 by vluo              #+#    #+#             */
/*   Updated: 2025/06/05 15:25:29 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_img *img, t_pos *a, int color, int do_free)
{
	char	*dst;

	if (a-> x > 0 && a -> x < RES_X && a-> y > 0 && a -> y < RES_Y)
	{
		dst = img->addr + ((int)a->y * img->lin_len
				+ (int)a->x * (img->b_p_p / 8));
		*(unsigned int *) dst = color;
	}
	if (do_free)
		free(a);
}

void	draw_hline(t_img *img, t_pos *st, t_pos *d, int color)
{
	int		i;
	int		p;
	int		y;
	int		dir;

	if (d->x == 0)
		return ;
	dir = 1;
	if (d->y < 0)
		dir = -1;
	d->y *= dir;
	y = st->y;
	p = (2 * d->y) - d->x;
	i = -1;
	while (++i < d->x + 1)
	{
		put_pixel(img, init_pos(st->x + i, y), color, 1);
		if (p >= 0)
		{
			y += dir;
			p -= (2 * d->x);
		}
		p += (2 * d->y);
	}
}

void	draw_vline(t_img *img, t_pos *st, t_pos *d, int color)
{
	int	i;
	int	p;
	int	x;
	int	dir;

	if (d->y == 0)
		return ;
	dir = 1;
	if (d->x < 0)
		dir = -1;
	d->x *= dir;
	x = st->x;
	i = -1;
	p = (2 * d->x) - d->y;
	while (++i < d->y + 1)
	{
		put_pixel(img, init_pos(x, st->y + i), color, 1);
		if (p >= 0)
		{
			x += dir;
			p -= (2 * d->y);
		}
		p += (2 * d->x);
	}
}

void	drawline(t_img *img, t_pos *a, t_pos *b, int color)
{
	t_pos	*d;

	if (abs((int)(b -> x - a -> x)) > abs((int)(b->y - a->y)))
	{
		if (a->x > b->x)
		{
			d = init_pos(a->x - b->x, a->y - b->y);
			return (draw_hline(img, b, d, color), free(d));
		}
		d = init_pos(b->x - a->x, b->y - a->y);
		return (draw_hline(img, a, d, color), free(d));
	}
	if (a->y > b->y)
	{
		d = init_pos(a->x - b->x, a->y - b->y);
		return (draw_vline(img, b, d, color), free(d));
	}
	d = init_pos(b->x - a->x, b->y - a->y);
	return (draw_vline(img, a, d, color), free(d));
}

void	draw_straight(t_img	*img, t_pos	*a, t_pos *b, int color)
{
	int	y;

	y = a -> y;
	while (y++ < b -> y)
		put_pixel(img, init_pos(a->x, y), color, 1);
}
