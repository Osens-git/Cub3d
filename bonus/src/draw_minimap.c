/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:36:03 by vluo              #+#    #+#             */
/*   Updated: 2025/06/10 18:01:35 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	*init_tab(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8)
{
	int	*t;

	t = calloc(8, sizeof(int));
	t[0] = n1;
	t[1] = n2;
	t[2] = n3;
	t[3] = n4;
	t[4] = n5;
	t[5] = n6;
	t[6] = n7;
	t[7] = n8;
	return (t);
}

int	**init_map(void)
{
	int	**map;

	map = calloc(8, sizeof(int *));
	map[0] = init_tab(1, 1, 1, 1, 1, 1, 1, 1);
	map[1] = init_tab(1, 0, 1, 0, 0, 1, 0, 1);
	map[2] = init_tab(1, 0, 1, 0, 0, 1, 0, 1);
	map[3] = init_tab(1, 0, 2, 1, 2, 1, 0, 1);
	map[4] = init_tab(1, 2, 2, 0, 0, 2, 0, 1);
	map[5] = init_tab(1, 0, 1, 1, 2, 1, 1, 1);
	map[6] = init_tab(1, 0, 0, 0, 0, 0, 0, 1);
	map[7] = init_tab(1, 1, 1, 1, 1, 1, 1, 1);
	return (map);
}

void	draw_player(t_data *data)
{
	float	ra;
	int		i;
	t_pos	pos_minimap;
	t_pos	d;
	t_pos	r;

	ra = limit_angle(data->p->a - DRAD * 30);
	i = -1;
	asign_pos(&pos_minimap, data->p->pos->x / 2, data->p->pos->y / 2);
	put_pixel(data -> minimap, &pos_minimap, 0x00FF1111, 0);
	while (++i < 120)
	{
		asign_pos(&d, cos(ra) * 5, sin(ra) * 5);
		asign_pos(&r, pos_minimap.x + (d.x * 5), pos_minimap.y + (d.y * 5));
		drawline(data -> minimap, &pos_minimap, &r, 0x00FFFFFF);
		ra = limit_angle(ra + DRAD / 2);
	}	
}

void	drawmap2d(t_data *data)
{
	int		i;
	int		color;
	t_pos	a;
	t_pos	b;
	t_pos	p;

	asign_pos(&p, -1, -1);
	while (++p.y < 8)
	{
		p.x = -1;
		while (++p.x < 8)
		{
			color = 0x0000008B;
			if (data -> map[(int)p.y][(int)p.x] >= 1)
				color = 0x00414e58;
			i = (p.x * (CELLSIZE / 2)) - 1;
			while (++i < (p.x * (CELLSIZE / 2)) + (CELLSIZE / 2))
			{
				asign_pos(&a, i, p.y * (CELLSIZE / 2));
				asign_pos(&b, i, (p.y * (CELLSIZE / 2)) + (CELLSIZE / 2));
				draw_straight(data -> minimap, &a, &b, color);
			}
		}
	}
	draw_player(data);
}
