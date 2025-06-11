/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:20:37 by vluo              #+#    #+#             */
/*   Updated: 2025/06/11 17:06:44 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	close_win(t_data *data)
{
	mlx_mouse_show(data->mlx, data->win);
	free_data(data);
	exit(1);
}

int	display(t_data *data)
{
	data -> frame ++;
	if (data -> frame == 2)
		return (1);
	if (data -> frame == 6)
		return (printf("4\n"), data -> frame = -1, 1);
	mlx_destroy_image(data -> mlx, data -> img -> img);
	free(data -> img);
	data -> img = init_img(data, NULL, RES_X, RES_Y);
	mlx_destroy_image(data -> mlx, data -> minimap -> img);
	free(data -> minimap);
	data -> minimap = init_img(data, NULL, 256, 256);
	mlx_do_sync(data->mlx);
	drawmap2d(data);
	drawrays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap->img, 10, 10);
	return (1);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	data -> mlx = mlx_init();
	data -> win = mlx_new_window(data -> mlx, RES_X, RES_Y, "CUB3D");
	data -> p = init_player(init_pos(4 * CELLSIZE,
				4 * CELLSIZE), 3 * PI / 2);
	data -> img = init_img(data, NULL, RES_X, RES_Y);
	data -> map = init_map();
	data -> floor_col = trgb(0, 108, 108, 108);
	data -> ceiling_col = trgb(0, 0, 80, 80);
	data -> minimap = init_img(data, NULL, 256, 256);
	data -> frame = -1;
	return (data);
}

int	main(void)
{
	t_data	*data;
	int		h;
	int		w;

	data = init_data();
	data -> no = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/north.xpm", &w, &h), 0, 0);
	data -> so = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/south.xpm", &w, &h), 0, 0);
	data -> ea = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/east.xpm", &w, &h), 0, 0);
	data -> we = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/west.xpm", &w, &h), 0, 0);
	data -> door = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/Tile_04.xpm", &w, &h), 0, 0);
	data -> door_open = init_img(data, mlx_xpm_file_to_image(data->mlx, "textures/blank.xpm", &w, &h), 0, 0);
	display(data);
	mlx_do_key_autorepeaton(data -> mlx);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_mouse_move(data->mlx, data->win, RES_X / 2, RES_Y / 2);
	mlx_hook(data -> win, 17, 0L, close_win, data);
	mlx_hook(data -> win, 06, 1L << 6, handle_mouse, data);
	mlx_hook(data -> win, 2, 1L << 0, handle_key_input, data);
	mlx_loop_hook(data->mlx, display, data);
	mlx_loop(data -> mlx);
}
