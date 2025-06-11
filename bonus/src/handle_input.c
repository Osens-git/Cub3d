/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:19:45 by vluo              #+#    #+#             */
/*   Updated: 2025/06/11 16:28:26 by vluo             ###   ########.fr       */
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

int	handle_door(t_data *data)
{
	int		i;
	float	ra;
	t_pos	d;
	t_pos	ray_cell;

	ra = limit_angle(data -> p -> a - DRAD * 30);
	i = -1;
	while (++i < 120)
	{
		asign_pos(&d, cos(ra) * 15, sin(ra) * 15);
		get_ray_cell(&ray_cell, &d, data);
		if (data->map[(int)ray_cell.y][(int)ray_cell.x] == 2)
			return (data->map[(int)ray_cell.y][(int)ray_cell.x] = -1, 1);
		if (data->map[(int)ray_cell.y][(int)ray_cell.x] == -1
			&& ((int)(data->p->pos->y / CELLSIZE) != (int)ray_cell.y
				|| (int)(data->p->pos->x / CELLSIZE) != (int)ray_cell.x))
			return (data->map[(int)ray_cell.y][(int)ray_cell.x] = 2, 1);
		ra = limit_angle(ra + DRAD / 2);
	}
	return (1);
}

int	handle_key_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		return (printf("%d (ESC) key pressed\n", keysym),
			free_data(data), exit(0), 0);
	if (keysym == XK_w || keysym == XK_a || keysym == XK_s || keysym == XK_d)
		return (handle_wasd(keysym, data), 1);
	if (keysym == XK_Left || keysym == XK_Right)
	{
		data->p->a = limit_angle(data->p->a + 0.1);
		if (keysym == XK_Left)
			data->p->a = limit_angle(data->p->a - 0.2);
		asign_pos(data->p->d, cos(data->p->a) * 5, sin(data->p->a) * 5);
		return (1);
	}
	if (keysym == XK_e)
		return (handle_door(data));
	return (1);
}
