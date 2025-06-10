/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:19:45 by vluo              #+#    #+#             */
/*   Updated: 2025/06/10 18:18:29 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	move_player(t_data *data, t_pos	*d)
{
	t_pos	m;
	t_pos	off;

	off.x = 20;
	if (d->x < 0)
		off.x = -20;
	off.y = 20;
	if (d->y < 0)
		off.y = -20;
	asign_pos(&off, (data->p->pos->x + off.x) / CELLSIZE,
		(data->p->pos->y + off.y) / CELLSIZE);
	asign_pos(&m, data->p->pos->x / CELLSIZE, data->p->pos->y / CELLSIZE);
	if (data->map[(int)m.y][(int)(off.x)] <= 0)
		asign_pos(data->p->pos, data->p->pos->x + d->x, data->p->pos->y);
	if (data->map[(int)(off.y)][(int)(m.x)] <= 0)
		asign_pos(data->p->pos, data->p->pos->x, data->p->pos->y + d->y);
}

static void	handle_wasd(int keysym, t_data *data)
{
	t_pos	dir;
	t_pos	d;
	t_pos	p;
	float	temp;

	asign_pos(&d, data->p->d->x, data->p->d->y);
	asign_pos(&p, data->p->pos->x, data->p->pos->y);
	if (keysym == XK_w || keysym == XK_s)
	{
		asign_pos(&dir, d.x, d.y);
		if (keysym == XK_s)
			asign_pos(&dir, -d.x, -d.y);
		move_player(data, &dir);
		return (display(data));
	}
	temp = data->p->a;
	temp = limit_angle(temp + PI / 2);
	if (keysym == XK_a)
		temp = limit_angle(temp - PI);
	asign_pos(&d, cos(temp) * 5, sin(temp) * 5);
	move_player(data, &d);
	display(data);
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
		asign_pos(&ray_cell, ((data->p->pos->x + d.x) / CELLSIZE) - 1,
			(data->p->pos->y + d.y) / CELLSIZE);
		if (data->map[(int)ray_cell.y][(int)ray_cell.x] == 2)
			return (data->map[(int)ray_cell.y][(int)ray_cell.x] = -1,
				display(data), 1);
		if (data->map[(int)ray_cell.y][(int)ray_cell.x] == -1
			&& ((int)(data->p->pos->y / CELLSIZE) != (int)ray_cell.y
				|| (int)(data->p->pos->x / CELLSIZE) != (int)ray_cell.x))
			return (data->map[(int)ray_cell.y][(int)ray_cell.x] = 2,
				display(data), 1);
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
		return (display(data), 1);
	}
	if (keysym == XK_e)
		return (handle_door(data));
	return (1);
}

int	handle_mouse(t_data *data)
{
	int	x;
	int	y;

	mlx_mouse_move(data->mlx, data->win, RES_X / 2, RES_Y / 2);
	mlx_mouse_get_pos(data -> mlx, data -> win, &x, &y);
	if (x != RES_X / 2)
	{
		if ((RES_X / 2) - x > 0)
			return (handle_key_input(XK_Left, data));
		return (handle_key_input(XK_Right, data));
	}
	return (1);
}
