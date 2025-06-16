/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:20:37 by vluo              #+#    #+#             */
/*   Updated: 2025/06/16 19:14:58 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	close_win(t_data *data)
{
	mlx_mouse_show(data->mlx, data->win);
	free_data(data);
	exit(1);
}

void	init_sprites(t_data *data)
{
	data -> sprites = ft_calloc(2, sizeof(t_sprite *));
	data -> sprites[0] = ft_calloc(1, sizeof(t_sprite));
	data -> sprites[0]-> textures = ft_calloc(6, sizeof(t_img));
	data -> sprites[0]-> textures[0] = init_img(data,
			xpm_img(data, "textures/Hand1.xpm"), 0, 0);
	data -> sprites[0]-> textures[1] = init_img(data,
			xpm_img(data, "textures/Hand2.xpm"), 0, 0);
	data -> sprites[0]-> textures[2] = init_img(data,
			xpm_img(data, "textures/Hand3.xpm"), 0, 0);
	data -> sprites[0]-> textures[3] = init_img(data,
			xpm_img(data, "textures/Hand4.xpm"), 0, 0);
	data -> sprites[0]-> textures[4] = init_img(data,
			xpm_img(data, "textures/Hand5.xpm"), 0, 0);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	data -> mlx = mlx_init();
	data -> win = mlx_new_window(data -> mlx, RES_X, RES_Y, "CUB3D");
	data -> p = init_player(init_pos(7 * CELLSIZE, 4 * CELLSIZE), PI);
	data -> img = init_img(data, NULL, RES_X, RES_Y);
	data -> map = init_map();
	data -> m_size = init_pos(8, 8);
	data -> floor_col = trgb(0, 108, 108, 108);
	data -> ceiling_col = trgb(0, 0, 80, 80);
	data -> minimap = init_img(data, NULL, 256, 256);
	data -> frame = -1;
	data->no = init_img(data, xpm_img(data, "textures/north.xpm"), 0, 0);
	data->so = init_img(data, xpm_img(data, "textures/south.xpm"), 0, 0);
	data->ea = init_img(data, xpm_img(data, "textures/east.xpm"), 0, 0);
	data->we = init_img(data, xpm_img(data, "textures/west.xpm"), 0, 0);
	data->d = init_img(data, xpm_img(data, "textures/Tile_04.xpm"), 0, 0);
	data->d_open = init_img(data, xpm_img(data, "textures/blank.xpm"), 0, 0);
	init_sprites(data);
	return (data);
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	display(data);
	mlx_do_key_autorepeatoff(data -> mlx);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_mouse_move(data->mlx, data->win, RES_X / 2, RES_Y / 2);
	mlx_hook(data -> win, 17, 0L, close_win, data);
	mlx_hook(data -> win, 06, 1L << 6, handle_mouse, data);
	mlx_hook(data -> win, 2, 1L << 0, handle_key_input, data);
	mlx_hook(data -> win, 3, 1L << 1, key_up, data);
	mlx_loop_hook(data->mlx, display, data);
	mlx_loop(data -> mlx);
}
