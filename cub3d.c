/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:20:37 by vluo              #+#    #+#             */
/*   Updated: 2025/06/04 18:19:43 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_data *data)
{
	free_data(data);
	exit(1);
}


void	display(t_data *data, int i)
{
	t_img	*img;
	t_pos	r;

	img = init_img(data, NULL);
	drawmap2d(img, data);
	if (i != 0)
		drawrays(img, data);
	asign_pos(&r, data->p->pos -> x + (data->p->d->x * 5),
		data->p->pos -> y + (data->p->d->y * 5));
	put_pixel(img, data->p->pos, 0x00FF0000, 0);
	drawline(img, data->p->pos, &r, 0x00FFFFFF);
	mlx_put_image_to_window(data->mlx, data->win, img->img, 0, 0);
	mlx_destroy_image(data -> mlx, data -> img -> img);
	free(data -> img);
	data -> img = img;
}

int	handle_key_input(int keysym, t_data *data)
{
	t_pos	dir;

	if (keysym == XK_Escape)
		return (printf("%d (ESC) key pressed\n", keysym),
			free_data(data), exit(0), 0);
	if (keysym == XK_w || keysym == XK_s)
	{
		asign_pos(&dir, data->p->d->x, data->p->d->y);
		if (keysym == XK_s)
			asign_pos(&dir, -data->p->d->x, -data->p->d->y);
		if (data->p->pos->x + dir.x > 0 && data->p->pos->x + dir.x < RES_X
			&& data->p->pos->y + dir.y > 0 && data->p->pos->y + dir.y < RES_Y)
			asign_pos(data->p->pos, data->p->pos->x + dir.x,
				data->p->pos->y + dir.y);
	}
	if (keysym == XK_a || keysym == XK_d)
	{
		data->p->a = limit_angle(data->p->a + 0.1);
		if (keysym == XK_a)
			data->p->a = limit_angle(data->p->a - 0.2);
		asign_pos(data->p->d, cos(data->p->a) * 5, sin(data->p->a) * 5);
	}
	return (display(data, 1), 1);
}

t_data	*init_data()
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	data -> mlx = mlx_init();
	data -> win = mlx_new_window(data -> mlx, RES_X, RES_Y, "CUB3D");
	data -> p = init_player(init_pos(5 * CELLSIZE, 5 * CELLSIZE), PI);
	data -> img = init_img(data, NULL);
	data -> map = init_map();
	data -> floor_col = trgb(0, 128, 128, 128);
	data -> ceiling_col = trgb(0, 0, 255, 255);
	return (data);
}

// void	re_draw(char *texture, t_data *data)
// {
// 	int		width;
// 	int		height;
// 	int		x;
// 	int		y;
// 	char	*color;

// 	data -> no = init_img(data, mlx_xpm_file_to_image(data->mlx,
// 				texture, &width, &height));
// 	y = -1;
// 	while (++y < height)
// 	{
// 		x = -1;
// 		while (++x < width)
// 		{
// 			color = data->no->addr + (y * data->no->line_length + x * (data->no->b_p_p / 8));
// 			put_pixel(data -> img, init_pos(RES_X / 2 + x, RES_Y / 2 + y), *(unsigned int*)color, 1);
// 		}
// 	}
// }

int	main(void)
{
	t_data	*data;
	t_pos	r;
	int		h;
	int		w;

	data = init_data();
	data -> no = init_img(data, mlx_xpm_file_to_image(data->mlx, "north.xpm", &w, &h));
	data -> so = init_img(data, mlx_xpm_file_to_image(data->mlx, "south.xpm", &w, &h));
	data -> ea = init_img(data, mlx_xpm_file_to_image(data->mlx, "east.xpm", &w, &h));
	data -> we = init_img(data, mlx_xpm_file_to_image(data->mlx, "west.xpm", &w, &h));
	asign_pos(&r, data -> p -> pos -> x + (data -> p -> d->x * 5),
		data -> p -> pos -> y + (data -> p -> d->y * 5));
	drawmap2d(data -> img, data);
	put_pixel(data -> img, data -> p -> pos, 0x00FF0000, 0);
	drawline(data -> img, data -> p -> pos, &r, 0x00FFFFFF);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	mlx_do_key_autorepeaton(data -> mlx);
	mlx_hook(data -> win, 17, 0L, close_win, data);
	mlx_hook(data -> win, 2, 1L << 0, handle_key_input, data);
	mlx_loop(data -> mlx);
}
 