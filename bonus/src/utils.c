/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:24:51 by vluo              #+#    #+#             */
/*   Updated: 2025/06/22 19:40:27 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

t_img	*init_img(t_data *data, void *img_ptr, int res_x, int res_y)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (img_ptr == NULL)
		img -> img = mlx_new_image(data->mlx, res_x, res_y);
	else
		img -> img = img_ptr;
	img -> addr = mlx_get_data_addr(img->img, &img->b_p_p,
			&img->lin_len, &img->endian);
	return (img);
}

t_player	*init_player(t_data *data, t_pos *pos_init, char dir)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	player -> pos = pos_init;
	if (dir == 'N')
		player -> a = PI / 2;
	if (dir == 'S')
		player -> a = 3 * PI / 2;
	if (dir == 'E')
		player -> a = PI;
	if (dir == 'W')
		player -> a = 0;
	player -> d = init_pos(cos(player->a) * 1.7, sin(player->a) * 1.7);
	data -> p = player;
	data -> p -> k_w = 0;
	data -> p -> k_a = 0;
	data -> p -> k_s = 0;
	data -> p -> k_d = 0;
	data -> p -> k_l = 0;
	data -> p -> k_r = 0;
	return (player);
}

t_pos	*init_pos(float x, float y)
{
	t_pos	*p;

	p = ft_calloc(1, sizeof(t_pos));
	p -> x = x;
	p -> y = y;
	return (p);
}

void	asign_pos(t_pos *pos, float x, float y)
{
	pos -> x = x;
	pos -> y = y;
}

void	init_minimap(t_data *data)
{
	t_pos	mini_size;

	asign_pos(&mini_size, 4 * CELLSIZE, 0);
	if (data -> m_size -> x <= 8)
		asign_pos(&mini_size, data->m_size->x * CELLSIZE / 2, 0);
	asign_pos(&mini_size, mini_size.x, 4 * CELLSIZE);
	if (data -> m_size -> y <= 8)
		asign_pos(&mini_size, mini_size.x, data->m_size->y * CELLSIZE / 2);
	data -> minimap -> size = init_pos(mini_size.x, mini_size.y);
	data -> minimap -> m = init_img(data, NULL, mini_size.x, mini_size.y);
	data -> minimap -> st = init_pos(0, 0);
	data -> minimap -> end = init_pos(0, 0);
}
