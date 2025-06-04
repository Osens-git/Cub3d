/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:20:37 by vluo              #+#    #+#             */
/*   Updated: 2025/06/04 19:27:14 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	t_pos	p;
	t_pos	d;
	float	temp;

	if (keysym == XK_Escape)
		return (printf("%d (ESC) key pressed\n", keysym),
			free_data(data), exit(0), 0);
	asign_pos(&d, data->p->d->x, data->p->d->y);
	asign_pos(&p, data->p->pos->x, data->p->pos->y);
	if (keysym == XK_w || keysym == XK_s)
	{
		asign_pos(&dir, d.x, d.y);
		if (keysym == XK_s)
			asign_pos(&dir, -d.x, -d.y);
		if (is_pos_in_res(p.x + dir.x, p.y + dir.y))
			asign_pos(data->p->pos, p.x+ dir.x, p.y + dir.y);
	}
	if (keysym == XK_a || keysym == XK_d)
	{
		temp = data->p->a;
		temp = limit_angle(temp + PI / 2);
		if (keysym == XK_a)
			temp = limit_angle(temp - PI);
		asign_pos(data->p->d, cos(temp) * 5, sin(temp) * 5);
		if (is_pos_in_res(p.x + data->p->d->x, p.y + data->p->d->y))
			asign_pos(data->p->pos, p.x + data->p->d->x, p.y + data->p->d->y);
		asign_pos(data->p->d, cos(data->p->a) * 5, sin(data->p->a) * 5);
	}
	if (keysym == XK_Left || keysym == XK_Right)
	{
		data->p->a = limit_angle(data->p->a + 0.1);
		if (keysym == XK_Left)
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

int	main(void)
{
	t_data	*data;
	t_pos	r;
	int		h;
	int		w;

	data = init_data();
	data -> no = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/north.xpm", &w, &h));
	data -> so = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/south.xpm", &w, &h));
	data -> ea = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/east.xpm", &w, &h));
	data -> we = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/west.xpm", &w, &h));
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
 