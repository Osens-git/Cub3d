/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_near_door.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:07:02 by vluo              #+#    #+#             */
/*   Updated: 2025/06/16 16:07:51 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	get_ray_cell(t_pos *ray_cell, t_pos *d, t_data *data)
{
	if (!(PI / 4 <= data->p->a && data->p->a <= 7 * PI / 4))
		asign_pos(ray_cell, ((data->p->pos->x + d->x) / CELLSIZE) + 1,
			(data->p->pos->y + d->y) / CELLSIZE);
	if (PI / 4 <= data->p->a && data->p->a <= 3 * PI / 4)
		asign_pos(ray_cell, ((data->p->pos->x + d->x) / CELLSIZE),
			((data->p->pos->y + d->y) / CELLSIZE) + 1);
	if (3 * PI / 4 <= data->p->a && data->p->a <= 5 * PI / 4)
		asign_pos(ray_cell, ((data->p->pos->x + d->x) / CELLSIZE) - 1,
			(data->p->pos->y + d->y) / CELLSIZE);
	if (5 * PI / 4 <= data->p->a && data->p->a <= 7 * PI / 4)
		asign_pos(ray_cell, ((data->p->pos->x + d->x) / CELLSIZE),
			((data->p->pos->y + d->y) / CELLSIZE) - 1);
}

int	check_door(t_data *data)
{
	int		i;
	float	ra;
	t_pos	d;
	t_pos	ray_cell;

	ra = limit_angle(data -> p -> a - DRAD * 30);
	i = -1;
	while (++i < 240)
	{
		asign_pos(&d, cos(ra) * 15, sin(ra) * 15);
		get_ray_cell(&ray_cell, &d, data);
		if (data->map[(int)ray_cell.y][(int)ray_cell.x] == 2)
			return (asign_pos(data->p->near_door, ray_cell.x, ray_cell.y),
				data->p->can_open = 1, 1);
		if (data->map[(int)ray_cell.y][(int)ray_cell.x] == -1
			&& ((int)(data->p->pos->y / CELLSIZE) != (int)ray_cell.y
				|| (int)(data->p->pos->x / CELLSIZE) != (int)ray_cell.x))
			return (asign_pos(data->p->near_door, ray_cell.x, ray_cell.y),
				data->p->can_close = 1, 1);
		ra = limit_angle(ra + DRAD / 4);
	}
	return (data->p->can_close = 0, data->p->can_open = 0, 0);
}
