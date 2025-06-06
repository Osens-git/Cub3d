/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_min_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:04:38 by vluo              #+#    #+#             */
/*   Updated: 2025/06/06 16:17:36 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_hr(t_pos *r, t_pos *off, t_pos *hray, t_data *data)
{
	t_pos	m;
	int		step;

	step = -1;
	while (++step < 8)
	{
		asign_pos(&m, r->x / CELLSIZE, r->y / CELLSIZE);
		if (m.x > 0 && m.x < 8 && m.y > 0 && m.y < 8
			&& data -> map[(int)m.y][(int)m.x] == 1)
			return (asign_pos(hray, r->x, r->y));
		asign_pos(r, r->x + off->x, r->y + off->y);
	}
	return (asign_pos(hray, r->x, r->y));
}

void	get_hray(float ra, t_pos *hray, t_data *data)
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
	return (get_hr(&r, &off, hray, data));
}

static void	get_vr(t_pos *r, t_pos *off, t_pos *vray, t_data *data)
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
				return (asign_pos(vray, r->x, r->y));
		}
		asign_pos(r, r->x + off->x, r->y + off->y);
	}
	return (asign_pos(vray, r->x, r->y));
}

void	get_vray(float ra, t_pos *vray, t_data *data)
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
		asign_pos(&r,
			data->p->pos->x - ((int)roundf(data->p->pos->x) % CELLSIZE),
			data->p->pos->y);
	return (get_vr(&r, &off, vray, data));
}
