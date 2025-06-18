/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:20:37 by vluo              #+#    #+#             */
/*   Updated: 2025/06/17 13:49:01 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display(t_data *data)
{
	mlx_clear_window(data->mlx, data -> win);
	drawrays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

t_data	*init_data(void)
{
	t_data	*data;
	int		w;
	int		h;

	data = ft_calloc(1, sizeof(t_data));
	data -> mlx = mlx_init();
	data -> win = mlx_new_window(data -> mlx, RES_X, RES_Y, "CUB3D");
	data -> p = init_player(init_pos(5 * CELLSIZE + (CELLSIZE / 2),
				5 * CELLSIZE + (CELLSIZE / 2)), 0);
	data -> img = init_img(data, NULL);
	data -> map = init_map();
	data -> m_size = init_pos(9, 8);
	data -> floor_col = trgb(0, 128, 128, 128);
	data -> ceiling_col = trgb(0, 0, 255, 255);
	data -> no = init_img(data,
			mlx_xpm_file_to_image(data->mlx, "textures/north.xpm", &w, &h));
	data -> so = init_img(data,
			mlx_xpm_file_to_image(data->mlx, "textures/south.xpm", &w, &h));
	data -> ea = init_img(data,
			mlx_xpm_file_to_image(data->mlx, "textures/east.xpm", &w, &h));
	data -> we = init_img(data,
			mlx_xpm_file_to_image(data->mlx, "textures/west.xpm", &w, &h));
	return (data);
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	display(data);
	mlx_do_key_autorepeaton(data -> mlx);
	mlx_hook(data -> win, 17, 0L, close_win, data);
	mlx_hook(data -> win, 2, 1L << 0, handle_key_input, data);
	mlx_loop(data -> mlx);
}
