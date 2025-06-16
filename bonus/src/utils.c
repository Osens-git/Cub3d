/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:24:51 by vluo              #+#    #+#             */
/*   Updated: 2025/06/16 19:11:38 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

t_img	*init_img(t_data *data, void *img_ptr, int res_x, int res_y)
{
	t_img	*img;

	img = calloc(1, sizeof(t_img));
	if (img_ptr == NULL)
		img -> img = mlx_new_image(data->mlx, res_x, res_y);
	else
		img -> img = img_ptr;
	img -> addr = mlx_get_data_addr(img->img, &img->b_p_p,
			&img->lin_len, &img->endian);
	return (img);
}

t_player	*init_player(t_pos *pos_init, float angle_init)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	player -> pos = pos_init;
	player -> a = angle_init;
	player -> d = init_pos(cos(player->a) * 1.9, sin(player->a) * 1.9);
	player -> near_door = init_pos(-1, -1);
	player -> k_w = 0;
	player -> k_a = 0;
	player -> k_s = 0;
	player -> k_d = 0;
	player -> k_l = 0;
	player -> k_r = 0;
	return (player);
}

t_pos	*init_pos(float x, float y)
{
	t_pos	*p;

	p = calloc(1, sizeof(t_pos));
	p -> x = x;
	p -> y = y;
	return (p);
}

void	asign_pos(t_pos *pos, float x, float y)
{
	pos -> x = x;
	pos -> y = y;
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->m_size->y)
		free(data->map[i]);
	mlx_do_key_autorepeaton(data -> mlx);
	return (free_img(data, data -> img), free_img(data, data -> no),
		free_img(data, data -> so), free_img(data, data -> ea),
		free_img(data, data -> we), free_img(data, data -> minimap),
		free_img(data, data -> d_open), free_img(data, data -> d),
		free_sprites(data), mlx_destroy_window(data->mlx, data->win),
		mlx_destroy_display(data->mlx), free(data->mlx), free(data->p->pos),
		free(data->p->d), free(data->p->near_door), free(data->p),
		free(data->map), free(data->m_size), free(data));
}
