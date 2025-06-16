/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:19:45 by vluo              #+#    #+#             */
/*   Updated: 2025/06/16 18:30:06 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	handle_door(t_data	*data)
{
	t_pos	door;

	asign_pos(&door, data->p->near_door->x, data->p->near_door->y);
	if (data->p->can_open)
	{
		data->map[(int)door.y][(int)door.x] = -1;
		data->p->can_open = 0;
	}
	if (data->p->can_close)
	{
		data->map[(int)door.y][(int)door.x] = 2;
		data->p->can_close = 0;
	}
}

int	handle_key_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		return (printf("%d (ESC) key pressed\n", keysym),
			free_data(data), exit(0), 0);
	if (keysym == XK_w)
		data -> p -> k_w = 1;
	if (keysym == XK_a)
		data -> p -> k_a = 1;
	if (keysym == XK_s)
		data -> p -> k_s = 1;
	if (keysym == XK_d)
		data -> p -> k_d = 1;
	if (keysym == XK_Left)
		data -> p -> k_l = 1;
	if (keysym == XK_Right)
		data -> p -> k_r = 1;
	if (keysym == XK_e && (data->p->can_close || data->p->can_open))
		return (handle_door(data), 1);
	return (1);
}

int	key_up(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data -> p -> k_w = 0;
	if (keysym == XK_a)
		data -> p -> k_a = 0;
	if (keysym == XK_s)
		data -> p -> k_s = 0;
	if (keysym == XK_d)
		data -> p -> k_d = 0;
	if (keysym == XK_Left)
		data -> p -> k_l = 0;
	if (keysym == XK_Right)
		data -> p -> k_r = 0;
	return (1);
}
