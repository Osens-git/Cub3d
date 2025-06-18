/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:36:03 by vluo              #+#    #+#             */
/*   Updated: 2025/06/17 17:36:39 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	*init_tab(int n1, int n2, int n3, int n4)
{
	int	*t;

	t = ft_calloc(5, sizeof(int));
	t[0] = n1;
	t[1] = n2;
	t[2] = n3;
	t[3] = n4;
	return (t);
}

int	**init_map(void)
{
	int	**map;

	map = ft_calloc(15, sizeof(int *));
	map[0] = init_tab(1, 1, 1, 1);
	map[1] = init_tab(1, 0, 0, 1);
	map[2] = init_tab(1, 0, 0, 1);
	map[3] = init_tab(1, 0, 0, 1);
	map[4] = init_tab(1, 0, 1, 1);
	map[5] = init_tab(1, 0, 0, 1);
	map[6] = init_tab(1, 1, 0, 1);
	map[7] = init_tab(1, 0, 0, 1);
	map[8] = init_tab(1, 0, 0, 1);
	map[9] = init_tab(1, 0, 1, 1);
	map[10] = init_tab(1, 0, 0, 1);
	map[11] = init_tab(1, 1, 0, 1);
	map[12] = init_tab(1, 0, 0, 1);
	map[13] = init_tab(1, 1, 1, 1);
	return (map);
}

void	draw_minimap_ray(t_data *data, t_ray *ray, t_pos *mp)
{
	t_pos	minimap_ray;

	asign_pos(&minimap_ray,
		(ray->mindist.x / 2) - (data->minimap->st->x * CELLSIZE / 2),
		(ray->mindist.y / 2) - (data->minimap->st->y * CELLSIZE / 2));
	if (minimap_ray.x < 0)
		minimap_ray.x = 0;
	if (minimap_ray.x > data -> minimap -> size -> x)
		minimap_ray.x = data -> minimap -> size -> x;
	if (minimap_ray.y < 0)
		minimap_ray.y = 0;
	if (minimap_ray.y > data -> minimap -> size -> y)
		minimap_ray.y = data -> minimap -> size -> y;
	drawline(data->minimap->m, mp, &minimap_ray, 0x00ffffff);
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

	asign_pos(&m, (int)(d->p->pos->x / CELLSIZE),
		(int)(d->p->pos->y / CELLSIZE));
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
					(((p.y - d->minimap->st->y) + 1) * (CELLSIZE / 2)));
				draw_straight(d->minimap->m, &a, &b, get_cell_color(d, p));
			}
		}
	}
}
