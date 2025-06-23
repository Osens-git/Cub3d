/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:36:03 by vluo              #+#    #+#             */
/*   Updated: 2025/06/23 12:51:07 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_minimap_player(t_data *data)
{
	t_pos	st;
	t_pos	end;
	t_pos	t_st;
	t_pos	t_end;
	t_pos	mp;

	asign_pos(&mp,
		(data->p->pos->x / 2) - (data->minimap->st->x * CELLSIZE / 2),
		(data->p->pos->y / 2) - (data->minimap->st->y * CELLSIZE / 2));
	asign_pos(&st, mp.x - 5, mp.y - 5);
	if (st.x < 0)
		st.x = 0;
	if (st.y > data -> minimap -> size -> y)
		st.y = data -> minimap -> size -> y;
	asign_pos(&end, mp.x + 5, mp.y + 5);
	if (end.x < 0)
		end.x = 0;
	if (end.y > data -> minimap -> size -> y)
		end.y = data -> minimap -> size -> y;
	while (++st.x < end.x)
	{
		asign_pos(&t_st, st.x - 1, st.y);
		asign_pos(&t_end, st.x - 1, end.y);
		draw_straight(data->minimap->m, &t_st, &t_end, 0x00FF0000);
	}
}

int	get_cell_color(t_data *data, t_pos p)
{
	if (data-> map[(int)p.y][(int)p.x] == 0)
		return (0x0000008B);
	if (data-> map[(int)p.y][(int)p.x] == 1)
		return (0x00414e58);
	if (data-> map[(int)p.y][(int)p.x] == 2)
		return (0x0006402B);
	return (0x003b3b3b);
}

static void	get_min_size(t_data *data)
{
	if (data -> m_size -> x <= 8)
	{
		data->minimap->st->x = 0;
		data->minimap->end->x = data -> m_size -> x;
	}
	if (data -> m_size -> y <= 8)
	{
		data->minimap->st->y = 0;
		data->minimap->end->y = data -> m_size -> y;
	}
}

static void	get_center_mini(t_data *data, t_pos *m)
{
	asign_pos(m, (int)m->x, (int)m->y);
	asign_pos(data -> minimap -> st, m->x - 4, m->y - 4);
	asign_pos(data -> minimap -> end, m->x + 4, m->y + 4);
	if (m->x + 4 >= data -> m_size -> x)
	{
		data->minimap->end->x = data -> m_size -> x;
		data->minimap->st->x = data -> m_size -> x - 8;
	}
	if (m->x - 4 <= 0)
	{
		data->minimap->st->x = 0;
		data->minimap->end->x = 8;
	}
	if (m->y + 4 >= data -> m_size -> y)
	{
		data->minimap->end->y = data -> m_size -> y;
		data->minimap->st->y = data -> m_size -> y - 8;
	}
	if (m->y - 4 <= 0)
	{
		data->minimap->st->y = 0;
		data->minimap->end->y = 8;
	}
	get_min_size(data);
}

void	drawm_minimap(t_data *d)
{
	int		i;
	t_pos	a;
	t_pos	b;
	t_pos	p;
	t_pos	m;

	asign_pos(&m, (d->p->pos->x / CELLSIZE), (d->p->pos->y / CELLSIZE));
	get_center_mini(d, &m);
	asign_pos(&p, d->minimap->st->x - 1, d->minimap->st->y - 1);
	while (++p.y < d->minimap->end->y)
	{
		p.x = d->minimap->st->x - 1;
		while (++p.x < d->minimap->end->x)
		{
			i = ((p.x - d->minimap->st->x) * (CELLSIZE / 2)) - 1;
			while (++i < (((p.x - d->minimap->st->x) + 1) * (CELLSIZE / 2)))
			{
				asign_pos(&a, i, (p.y - d->minimap->st->y) * (CELLSIZE / 2));
				asign_pos(&b, i,
					(p.y - d->minimap->st->y + 1) * (CELLSIZE / 2));
				draw_straight(d->minimap->m, &a, &b, get_cell_color(d, p));
			}
		}
	}
	draw_minimap_player(d);
}
