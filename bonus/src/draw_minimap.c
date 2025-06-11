/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:36:03 by vluo              #+#    #+#             */
/*   Updated: 2025/06/11 15:13:21 by vluo             ###   ########.fr       */
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
	map[1] = init_tab(1, 0, 1, 0, 2, 1, 0, 1);
	map[2] = init_tab(1, 0, 1, 0, 0, 1, 0, 1);
	map[3] = init_tab(1, 0, 1, 0, 0, 1, 0, 1);
	map[4] = init_tab(1, 0, 0, 0, 0, 2, 0, 1);
	map[5] = init_tab(1, 0, 1, 1, 0, 1, 1, 1);
	map[6] = init_tab(1, 0, 0, 0, 0, 0, 0, 1);
	map[7] = init_tab(1, 1, 1, 1, 1, 1, 1, 1);
	return (map);
}

int	get_cell_color(t_data *data, int x, int y)
{
	if (data-> map[y][x] == 0)
		return (0x0000008B);
	if (data-> map[y][x] == 1)
		return (0x00414e58);
	if (data-> map[y][x] == 2)
		return (0x0006402B);
	return (0x003b3b3b);
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
			color = get_cell_color(data, (int)p.x, (int)p.y);
			i = (p.x * (CELLSIZE / 2)) - 1;
			while (++i < (p.x * (CELLSIZE / 2)) + (CELLSIZE / 2))
			{
				asign_pos(&a, i, p.y * (CELLSIZE / 2));
				asign_pos(&b, i, (p.y * (CELLSIZE / 2)) + (CELLSIZE / 2));
				draw_straight(data -> minimap, &a, &b, color);
			}
		}
	}
}
