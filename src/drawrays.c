/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawrays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:32:40 by vluo              #+#    #+#             */
/*   Updated: 2025/06/04 18:48:15 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_pos	*get_hr(t_pos *r, t_pos *off, t_data *data)
{
	t_pos	m;
	int		step;

	step = -1;

	while (++step < 8)
	{
		asign_pos(&m, r->x / CELLSIZE, r->y / CELLSIZE);
		if (m.x > 0 && m.x < 8 && m.y > 0 && m.y < 8
			&& data -> map[(int)m.y][(int)m.x] == 1)
			return (init_pos(r->x, r->y));
		asign_pos(r, r->x + off->x, r->y + off->y);
	}
	return (init_pos(r->x, r->y));
}

static t_pos	*get_hray(float ra, t_data *data)
{
	t_pos	r;
	t_pos	off;

	if (ra > PI)
	{
		r.y = (((int)data->p->pos->y / CELLSIZE) * CELLSIZE) - 0.0001;
		r.x = ((data->p->pos->y - r.y) * (-1 / tan(ra)) + data->p->pos->x);
		asign_pos(&off, -(-CELLSIZE) * (-1 / tan(ra)), -CELLSIZE);
	}
	if (ra < PI)
	{
		r.y = (((int)data->p->pos->y / CELLSIZE) * CELLSIZE) + CELLSIZE;
		r.x = ((data->p->pos->y - r.y) * (-1 / tan(ra)) + data->p->pos->x);
		asign_pos(&off, -(CELLSIZE) * (-1 / tan(ra)), CELLSIZE);
	}
	if (ra == 0 || (PI - 0.0001 < ra && ra < PI + 0.0001))
		asign_pos(&r, data->p->pos->x, data->p->pos->y);
	return (get_hr(&r, &off, data));
}

static t_pos	*get_vr(t_pos *r, t_pos *off, t_data *data)
{
	int		step;
	t_pos	m;

	step = -1;
	while (++step < 8)
	{
		asign_pos(&m, r->x / CELLSIZE, r->y / CELLSIZE);
		if (m.x > 0 && m.x < 8 && m.y > 0 && m.y < 8)
		{
			if ((int)r->x % CELLSIZE == 0)
				if (off->x < 0)
					m.x -= 1;
			if (data->map[(int)m.y][(int)m.x] == 1)
				return (init_pos(r->x, r->y));
		}
		asign_pos(r, r->x + off->x, r->y + off->y);
	}
	return (init_pos(r->x, r->y));
}

static t_pos	*get_vray(float ra, t_data *data)
{
	t_pos	r;
	t_pos	off;

	if (ra > PI / 2 && ra < 3 * PI / 2)
	{
		r.x = (((int)data->p->pos->x / CELLSIZE) * CELLSIZE) - 0.0001;
		r.y = ((data->p->pos->x - r.x) * (-tan(ra)) + data->p->pos->y);
		asign_pos(&off, -CELLSIZE, -(-CELLSIZE) * (-tan(ra)));
	}
	if (ra < PI / 2 || ra > 3 * PI / 2)
	{
		r.x = (((int)data->p->pos->x / CELLSIZE) * CELLSIZE) + CELLSIZE;
		r.y = ((data->p->pos->x - r.x) * (-tan(ra)) + data->p->pos->y);
		asign_pos(&off, CELLSIZE, -(CELLSIZE) * (-tan(ra)));
	}
	if (ra == 0 || (PI - 0.0001 < ra && ra < PI + 0.0001))
		asign_pos(&r, data->p->pos->x - ((int)data->p->pos->x % CELLSIZE),
			data->p->pos->y);
	return (get_vr(&r, &off, data));
}

void	drawline_texture(t_img *img, t_pos *a, t_img *tex, float hline, float tx, float ty_off, float ty_step)
{
	int		y;
	float	ty;
	char	*color;

	ty = ty_off * ty_step;
	y = a -> y;
	while (y++ < a -> y + hline)
	{
		color = tex->addr + (int)((int)ty * tex->line_length + tx * (tex->b_p_p / 8));
		put_pixel(img, init_pos(a->x, y), *(unsigned int*)color, 1);
		ty += ty_step;
	}
}

void	drawrays(t_img *img, t_data *data)
{
	int		j;
	int		i;
	float	ra;
	t_pos	*minhdist;
	t_pos	*minvdist;
	t_pos	mindist;
	float	hline;
	float	corr_angle;
	t_pos	a;
	t_pos	b;
	float	tx;
	float	ty_off;
	float	ty_step;
	t_img	*tex;

	ra = limit_angle(data->p->a - DRAD * 30);
	i = -1;
	while (++i < 240)
	{
		minhdist = get_hray(ra, data);
		minvdist = get_vray(ra, data);
		asign_pos(&mindist, minvdist->x, minvdist->y);
		if (dist(data->p->pos, minhdist) < dist(data->p->pos, minvdist))
			asign_pos(&mindist, minhdist->x, minhdist->y);
		drawline(img, data->p->pos, &mindist, 0x000000FF);
		corr_angle = limit_angle(data->p->a - ra);
		hline = (CELLSIZE * 320)
			/ (dist(&mindist, data->p->pos) * cos(corr_angle));
		ty_step = 32 / hline;
		ty_off = 0;
		if (hline >= RES_Y)
		{
			ty_off = (hline - RES_Y) / 2;
			hline = RES_Y;
		}
		tex = data -> ea;						// EAST
		tx = ((int)mindist.y / 2 % 32);
		if (PI / 2 <= ra && ra <= 3 * PI / 2)	// WEST
		{
			tex = data -> we;
			tx = 31 - ((int)mindist.y / 2 % 32);
		}
		if (dist(&mindist, data->p->pos) == dist(minhdist, data->p->pos))
		{
			tex = data -> no;					// NORTH
			tx = ((int)mindist.x / 2 % 32);
			if (0 <= ra && ra <= PI)			// SOUTH
			{
				tex = data -> so;
				tx = 31 - ((int)mindist.x / 2 % 32);
			}
		}
		j = -1;
		while (++j < 2)
		{
			asign_pos(&a, i * 2 + j + 530, 0);
			asign_pos(&b, i * 2 + j + 530, 256 - (hline / 2));
			drawline(img, &a, &b, data->ceiling_col);
			asign_pos(&a, i * 2 + j + 530, 256 - (hline / 2));
			asign_pos(&b, i * 2 + j + 530, hline + (256 - hline / 2));
			drawline_texture(img, &a, tex, hline, tx, ty_off, ty_step);
			asign_pos(&a, i * 2 + j + 530, hline + (256 - hline / 2));
			asign_pos(&b, i * 2 + j + 530, RES_Y);
			drawline(img, &a, &b, data->floor_col);
		}
		ra = limit_angle(ra + (DRAD / 4));
		free(minhdist);
		free(minvdist);
	}
}
