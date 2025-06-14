/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:24:51 by vluo              #+#    #+#             */
/*   Updated: 2025/06/11 14:53:51 by vluo             ###   ########.fr       */
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

	player = calloc(1, sizeof(t_player));
	player -> pos = pos_init;
	player -> a = angle_init;
	player -> d = init_pos(cos(player->a) * 5, sin(player->a) * 5);
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

	mlx_destroy_image(data -> mlx, data -> img -> img);
	free(data -> img);
	mlx_destroy_image(data -> mlx, data -> no -> img);
	free(data -> no);
	mlx_destroy_image(data -> mlx, data -> so -> img);
	free(data -> so);
	mlx_destroy_image(data -> mlx, data -> we -> img);
	free(data -> we);
	mlx_destroy_image(data -> mlx, data -> ea -> img);
	free(data -> ea);
	mlx_destroy_image(data -> mlx, data -> minimap -> img);
	free(data -> minimap);
	mlx_destroy_image(data -> mlx, data -> door_open -> img);
	free(data -> door_open);
	mlx_destroy_image(data -> mlx, data -> door -> img);
	free(data -> door);
	i = -1;
	while (++i < 8)
		free(data->map[i]);
	return (mlx_destroy_window(data->mlx, data->win),
		mlx_destroy_display(data->mlx), free(data->mlx), free(data->p->pos),
		free(data->p->d), free(data->p), free(data->map), free(data));
}
