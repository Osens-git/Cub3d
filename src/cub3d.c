/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:20:37 by vluo              #+#    #+#             */
/*   Updated: 2025/06/06 16:08:05 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display(t_data *data)
{
	// t_pos	r;

	mlx_destroy_image(data -> mlx, data -> img -> img);
	free(data -> img);
	data -> img = init_img(data, NULL);
	// drawmap2d(data);
	drawrays(data);
	// asign_pos(&r, data->p->pos -> x + (data->p->d->x * 5),
	// 	data->p->pos -> y + (data->p->d->y * 5));
	// put_pixel(data -> img, data->p->pos, 0x00FF0000, 0);
	// drawline(data -> img, data->p->pos, &r, 0x00FFFFFF);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	data -> mlx = mlx_init();
	data -> win = mlx_new_window(data -> mlx, RES_X, RES_Y, "CUB3D");
	data -> p = init_player(init_pos(5 * CELLSIZE, 5 * CELLSIZE), 3 * PI / 2);
	data -> img = init_img(data, NULL);
	data -> map = init_map();
	data -> floor_col = trgb(0, 128, 128, 128);
	data -> ceiling_col = trgb(0, 0, 255, 255);
	return (data);
}

int	main(void)
{
	t_data	*data;
	// t_pos	r;
	int		h;
	int		w;

	data = init_data();
	data -> no = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/north.xpm", &w, &h));
	data -> so = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/south.xpm", &w, &h));
	data -> ea = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/east.xpm", &w, &h));
	data -> we = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/west.xpm", &w, &h));
	// asign_pos(&r, data -> p -> pos -> x + (data -> p -> d->x * 5),
	// 	data -> p -> pos -> y + (data -> p -> d->y * 5));
	// drawmap2d(data);
	// put_pixel(data -> img, data -> p -> pos, 0x00FF0000, 0);
	// drawline(data -> img, data -> p -> pos, &r, 0x00FFFFFF);
	display(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	mlx_do_key_autorepeaton(data -> mlx);
	mlx_hook(data -> win, 17, 0L, close_win, data);
	mlx_hook(data -> win, 2, 1L << 0, handle_key_input, data);
	mlx_loop(data -> mlx);
}
