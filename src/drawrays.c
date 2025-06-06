/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawrays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:32:40 by vluo              #+#    #+#             */
/*   Updated: 2025/06/06 16:16:47 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_ray_dist(float ra, t_ray *ray, t_data *data)
{
	get_hray(ra, &ray->minhdist, data);
	get_vray(ra, &ray->minvdist, data);
	asign_pos(&ray->mindist, ray->minvdist.x, ray->minvdist.y);
	if (dist(data->p->pos, &ray->minhdist) < dist(data->p->pos, &ray->minvdist))
		asign_pos(&ray->mindist, ray->minhdist.x, ray->minhdist.y);
	ray->hline = (CELLSIZE * RES_Y) / (dist(&ray->mindist, data->p->pos)
			* cos(limit_angle(data->p->a - ra)));
	ray->hline = roundf(ray->hline);
	ray -> ty_step = 32 / ray -> hline;
	ray -> ty_off = 0;
	if (ray -> hline >= RES_Y)
	{
		ray -> ty_off = (ray -> hline - RES_Y) / 2;
		ray -> hline = RES_Y;
	}
}

static void	get_ray_tex(float ra, t_ray *ray, t_data *data)
{
	ray->tex = data -> ea;
	ray->tx = ((int)ray->mindist.y / 2 % 32);
	if (PI / 2 <= ra && ra <= 3 * PI / 2)
	{
		ray->tex = data -> we;
		ray->tx = 31 - ((int)ray->mindist.y / 2 % 32);
	}
	if (dist(&ray->mindist, data->p->pos) == dist(&ray->minhdist, data->p->pos))
	{
		ray->tex = data -> no;
		ray->tx = ((int)ray->mindist.x / 2 % 32);
		if (0 <= ra && ra <= PI)
		{
			ray->tex = data -> so;
			ray->tx = 31 - ((int)ray->mindist.x / 2 % 32);
		}
	}
}

static void	drawline_texture(t_img *img, t_pos *a, t_ray *ray)
{
	int		y;
	float	ty;
	char	*color;

	ty = ray->ty_off * ray->ty_step;
	y = a -> y;
	while (y++ < a -> y + ray -> hline)
	{
		color = ray->tex->addr + (int)((int)ty * ray->tex->lin_len
				+ ray->tx * (ray->tex->b_p_p / 8));
		put_pixel(img, init_pos(a->x, y), *(unsigned int *)color, 1);
		ty += ray -> ty_step;
	}
}

static void	draw_ray(int i, t_ray *ray, t_data *data)
{
	int		j;
	float	lineoff;
	t_pos	a;
	t_pos	b;

	lineoff = 320 - ((int)ray -> hline >> 1);
	j = -1;
	while (++j < 4)
	{
		asign_pos(&a, i * 4 + j, 0);
		asign_pos(&b, i * 4 + j, lineoff);
		draw_straight(data->img, &a, &b, data->ceiling_col);
		asign_pos(&a, i * 4 + j, lineoff);
		asign_pos(&b, i * 4 + j, ray->hline + lineoff);
		drawline_texture(data->img, &a, ray);
		asign_pos(&a, i * 4 + j, ray->hline + lineoff);
		asign_pos(&b, i * 4 + j, RES_Y);
		draw_straight(data->img, &a, &b, data->floor_col);
	}
}

void	drawrays(t_data *data)
{
	int		i;
	float	ra;
	t_ray	*ray;

	ra = limit_angle(data->p->a - DRAD * 30);
	i = -1;
	while (++i < 240)
	{
		ray = ft_calloc(1, sizeof(t_ray));
		get_ray_dist(ra, ray, data);
		// drawline(data -> img, data->p->pos, &ray->mindist, 0x000000FF);
		get_ray_tex(ra, ray, data);
		draw_ray(i, ray, data);
		free(ray);
		ra = limit_angle(ra + (DRAD / 4));
	}
}
