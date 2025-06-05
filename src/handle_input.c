/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:19:45 by vluo              #+#    #+#             */
/*   Updated: 2025/06/05 14:37:23 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_win(t_data *data)
{
	free_data(data);
	exit(1);
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
		if (is_pos_in_res(p.x + dir.x, p.y + dir.y))
			asign_pos(data->p->pos, p.x + dir.x, p.y + dir.y);
		return ;
	}
	temp = data->p->a;
	temp = limit_angle(temp + PI / 2);
	if (keysym == XK_a)
		temp = limit_angle(temp - PI);
	asign_pos(data->p->d, cos(temp) * 5, sin(temp) * 5);
	if (is_pos_in_res(p.x + data->p->d->x, p.y + data->p->d->y))
		asign_pos(data->p->pos, p.x + data->p->d->x, p.y + data->p->d->y);
	asign_pos(data->p->d, cos(data->p->a) * 5, sin(data->p->a) * 5);
}

int	handle_key_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		return (printf("%d (ESC) key pressed\n", keysym),
			free_data(data), exit(0), 0);
	if (keysym == XK_w || keysym == XK_a || keysym == XK_s || keysym == XK_d)
		handle_wasd(keysym, data);
	if (keysym == XK_Left || keysym == XK_Right)
	{
		data->p->a = limit_angle(data->p->a + 0.1);
		if (keysym == XK_Left)
			data->p->a = limit_angle(data->p->a - 0.2);
		asign_pos(data->p->d, cos(data->p->a) * 5, sin(data->p->a) * 5);
	}
	return (display(data), 1);
}
