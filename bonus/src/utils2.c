/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:52:18 by vluo              #+#    #+#             */
/*   Updated: 2025/06/17 17:30:03 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->m_size->y)
		free(data->map[i]);
	mlx_do_key_autorepeaton(data -> mlx);
	return (free_img(data, data -> img), free_img(data, data -> no),
		free_img(data, data -> so), free_img(data, data -> ea),
		free_img(data, data -> we), free_img(data, data -> minimap -> m),
		free_img(data, data -> d_open), free_img(data, data -> d),
		free_sprites(data), mlx_destroy_window(data->mlx, data->win),
		mlx_destroy_display(data->mlx), free(data->mlx), free(data->p->pos),
		free(data->p->d), free(data->p->near_door), free(data->p),
		free(data->minimap->st), free(data->minimap->end),
		free(data->minimap->size), free(data->minimap),
		free(data->map), free(data->m_size), free(data));
}

float	dist(t_pos *a, t_pos *b)
{
	return (sqrt((b->x - a->x) * (b->x - a->x)
			+ (b->y - a->y) * (b->y - a->y)));
}

float	limit_angle(float nb)
{
	if (nb > 2 * PI)
		return (nb - 2 * PI);
	if (nb < 0)
		return (nb + 2 * PI);
	return (nb);
}

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	get_dir_texture(t_ray *ray, t_pos r, t_data *d, int dir)
{
	if (dir == 1)
		ray->tex = d -> ea;
	if (dir == 1 && r.x - 1 >= 0 && d -> map[(int)r.y][(int)r.x - 1] == -1)
			ray->tex = d -> d_open;
	if (dir == 2)
		ray->tex = d -> we;
	if (dir == 2
		&& r.x + 1 < d->m_size->x && d->map[(int)r.y][(int)r.x + 1] == -1)
		ray->tex = d -> d_open;
	if (dir == 3)
		ray->tex = d -> no;
	if (dir == 3
		&& r.y + 1 < d->m_size->y && d->map[(int)r.y + 1][(int)r.x] == -1)
		ray->tex = d -> d_open;
	if (dir == 4)
		ray->tex = d -> so;
	if (dir == 4 && r.y - 1 >= 0 && d -> map[(int)r.y - 1][(int)r.x] == -1)
		ray->tex = d -> d_open;
}
