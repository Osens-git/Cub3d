/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:19:45 by vluo              #+#    #+#             */
/*   Updated: 2025/06/17 13:22:58 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_win(t_data *data)
{
	free_data(data);
	exit(1);
}

static void	move_straight(t_data *data, t_pos *p_pos, t_pos *d, float a)
{
	t_pos	end_add;
	t_pos	end_sub;
	t_pos	end_off;
	t_pos	off;

	asign_pos(&off, 15, 15);
	if (d->x < 0)
		off.x = -15;
	if (d->y < 0)
		off.y = -15;
	asign_pos(&end_add, (p_pos->x + d->x + 15) / CELLSIZE,
		(p_pos->y + d->y + 15) / CELLSIZE);
	asign_pos(&end_sub, (p_pos->x + d->x - 15) / CELLSIZE,
		(p_pos->y - d->y - 15) / CELLSIZE);
	asign_pos(&end_off, (p_pos->x + d->x + off.x) / CELLSIZE,
		(p_pos->y + d->y + off.y) / CELLSIZE);
	if ((PI - 0.001 <= a && a <= PI + 0.001) || (-0.001 <= a && a <= 0.001))
		if (data->map[(int)end_add.y][(int)end_off.x] <= 0
			&& data->map[(int)end_sub.y][(int)end_off.x] <= 0)
			return (asign_pos(p_pos, p_pos->x + d->x, p_pos->y));
	if (((PI / 2) - 0.001 <= a && a <= (PI / 2) + 0.001)
		|| ((3 * PI / 2) - 0.001 <= a && a <= (3 * PI / 2) + 0.001))
		if (data->map[(int)end_off.y][(int)end_add.x] <= 0
			&& data->map[(int)end_off.y][(int)end_sub.x] <= 0)
			return (asign_pos(p_pos, p_pos->x, p_pos->y + d->y));
}

static void	move_player(t_data *data, t_pos	*d)
{
	t_pos	end_pos;
	t_pos	m;
	t_pos	off;

	if ((PI - 0.001 <= data->p->a && data->p->a <= PI + 0.001)
		|| ((0 - 0.001 <= data->p->a && data->p->a <= 0 + 0.001))
		|| ((PI / 2) - 0.001 <= data->p->a
			&& data->p->a <= (PI / 2) + 0.001)
		|| ((3 * PI / 2) - 0.001 <= data->p->a
			&& data->p->a <= (3 * PI / 2) + 0.001))
		return (move_straight(data, data->p->pos, d, data->p->a));
	asign_pos(&end_pos, data->p->pos->x + d->x, data->p->pos->y + d->y);
	asign_pos(&m, data->p->pos->x / CELLSIZE, data->p->pos->y / CELLSIZE);
	asign_pos(&off, 18, 18);
	if (d->x < 0)
		off.x = -off.x;
	if (d->y < 0)
		off .y = -off.y;
	if (data->map[(int)end_pos.y / CELLSIZE]
		[(int)((end_pos.x + off.x) / CELLSIZE)] <= 0)
		asign_pos(data->p->pos, data->p->pos->x + d->x, data->p->pos->y);
	if (data->map[(int)(end_pos.y + off.y) / CELLSIZE]
			[(int)end_pos.x / CELLSIZE] <= 0)
		asign_pos(data->p->pos, data->p->pos->x, data->p->pos->y + d->y);
}

void	handle_wasd(int keysym, t_data *data)
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
	}
	if (keysym == XK_a || keysym == XK_d)
	{
		temp = data->p->a;
		data->p->a = limit_angle(data->p->a + PI / 2);
		if (keysym == XK_a)
			data->p->a = limit_angle(data->p->a - PI);
		asign_pos(&d, cos(data->p->a) * 5, sin(data->p->a) * 5);
		move_player(data, &d);
		data->p->a = temp;
	}
	display(data);
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
	return (1);
}
