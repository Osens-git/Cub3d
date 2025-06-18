/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawrays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:32:40 by vluo              #+#    #+#             */
/*   Updated: 2025/06/17 17:24:27 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	t_pos	r;

	asign_pos(&r, (int)(ray->mindist.x / CELLSIZE),
		(int)(ray->mindist.y / CELLSIZE));
	get_dir_texture(ray, r, data, 1);
	ray->tx = ((int)ray->mindist.y / 2 % 32);
	if (PI / 2 <= ra && ra <= 3 * PI / 2)
	{
		get_dir_texture(ray, r, data, 2);
		ray->tx = 31 - ((int)ray->mindist.y / 2 % 32);
	}
	if (dist(&ray->mindist, data->p->pos) == dist(&ray->minhdist, data->p->pos))
	{
		get_dir_texture(ray, r, data, 3);
		ray->tx = ((int)ray->mindist.x / 2 % 32);
		if (0 <= ra && ra <= PI)
		{
			get_dir_texture(ray, r, data, 4);
			ray->tx = 31 - ((int)ray->mindist.x / 2 % 32);
		}
	}
	if (data->map[(int)r.y][(int)r.x] == 2)
		ray -> tex = data -> d;
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
	t_pos	minimap_pos;

	ra = limit_angle(data->p->a - DRAD * 30);
	i = -1;
	asign_pos(&minimap_pos,
		(data->p->pos->x / 2) - (data->minimap->st->x * CELLSIZE / 2),
		(data->p->pos->y / 2) - (data->minimap->st->y * CELLSIZE / 2));
	while (++i < 240)
	{
		ray = ft_calloc(1, sizeof(t_ray));
		get_ray_dist(ra, ray, data);
		draw_minimap_ray(data, ray, &minimap_pos);
		get_ray_tex(ra, ray, data);
		draw_ray(i, ray, data);
		free(ray);
		ra = limit_angle(ra + (DRAD / 4));
	}
}
