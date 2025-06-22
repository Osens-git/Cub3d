/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:24:51 by vluo              #+#    #+#             */
/*   Updated: 2025/06/22 19:34:11 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	*init_img(t_data *data, void *img_ptr)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	if (img_ptr == NULL)
		img -> img = mlx_new_image(data->mlx, RES_X, RES_Y);
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
	player -> d = init_pos(cos(player->a) * 5, sin(player->a) * 5);
	data -> p = player;
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

void	free_data(t_data *data)
{
	if (data -> no)
		free_img(data, data -> no);
	if (data -> so)
		free_img(data, data -> so);
	if (data -> we)
		free_img(data, data -> we);
	if (data -> ea)
		free_img(data, data -> ea);
	if (data -> map)
		free_tab_int(data -> map);
	if (data -> p)
	{
		free(data -> p -> pos);
		free(data -> p -> d);
		free(data -> p);
	}
	return (mlx_destroy_image(data->mlx, data->img->img), free(data->img),
		mlx_destroy_window(data->mlx, data->win), free(data->m_size),
		mlx_destroy_display(data->mlx), free(data->mlx), free(data));
}
