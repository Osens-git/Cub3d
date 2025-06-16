/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:25:45 by vluo              #+#    #+#             */
/*   Updated: 2025/06/16 18:30:49 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	zoom(t_data *data, t_pos *tex, int color, int zoom)
{
	int	i;
	int	j;

	i = -1;
	while (++i < zoom)
	{
		j = -1;
		while (++j < zoom)
			put_pixel(data -> img, init_pos(
					(RES_X - 50) - ((64 * zoom) - (tex->x * zoom + i)),
					RES_Y - ((64 * zoom) - (tex->y * zoom + j))), color, 1);
	}
	free(tex);
}

void	drawsprite(t_data *data, t_sprite *sp)
{
	int		x;
	int		y;
	int		color;
	t_img	*text;

	if (sp->textures[sp->cur_text] == 0)
		sp->cur_text = 0;
	text = sp->textures[sp->cur_text];
	y = -1;
	while (++y < 64)
	{
		x = -1;
		while (++x < 64)
		{
			color = *(int *)(sp->textures[sp->cur_text]->addr
					+ (y * text->lin_len + x * (text->b_p_p / 8)));
			if (color == -16777216 || color == 0)
				continue ;
			zoom(data, init_pos(x, y), color, 3);
		}
	}
}

void	put_text(t_data *data, char *text)
{
	mlx_string_put(data -> mlx, data -> win,
		RES_X / 2, RES_Y / 2 + 150, 0x00FFFFFF, text);
}

int	display(t_data *data)
{
	data -> frame ++;
	if (data -> frame == 2)
		return (1);
	if (data -> frame == 6)
		return (data-> sprites[0]->cur_text ++, data->frame = -1, 1);
	mlx_clear_window(data->mlx, data->win);
	handle_wasd_keys(data);
	handle_lr_keys(data);
	drawmap2d(data);
	drawrays(data);
	drawsprite(data, data->sprites[0]);
	mlx_do_sync(data -> mlx);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap->img, 10, 10);
	if (check_door(data))
	{
		if (data->p->can_open)
			put_text(data, "Press (e) to open door");
		if (data->p->can_close)
			put_text(data, "Press (e) to close door");
	}
	return (1);
}
