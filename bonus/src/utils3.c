/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:53:31 by vluo              #+#    #+#             */
/*   Updated: 2025/06/10 17:39:47 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

int	hex_to_dec(char *nb)
{
	int	res;
	int	i;
	int	p;

	res = 0;
	p = 1;
	i = -1;
	while (nb[++i])
	{
		if (ft_isdigit(nb[ft_strlen(nb) - i - 1]) == 0)
			res = res + ((9 + ((nb[ft_strlen(nb) - i - 1] - '0') % 16)) * p);
		else
			res = res + ((nb[ft_strlen(nb) - i - 1] - '0') * (p));
		p = p * 16;
	}
	return (free(nb), res);
}

void	get_dir_texture(t_ray *ray, t_pos r, t_data *data, int dir)
{
	if (dir == 1)
	{
		ray->tex = data -> ea;
		if (r.x >= 0 && data -> map[(int)r.y][(int)r.x - 1] == -1)
			ray->tex = data -> door_open;
	}
	else if (dir == 2)
	{
		ray->tex = data -> we;
		if (r.x < 8 && data -> map[(int)r.y][(int)r.x + 1] == -1)
			ray->tex = data -> door_open;
	}
	else if (dir == 3)
	{
		ray->tex = data -> no;
		if (r.y + 1 < 8 && data -> map[(int)r.y + 1][(int)r.x] == -1)
			ray->tex = data -> door_open;
	}
	else
	{
		ray->tex = data -> so;
		if (r.y - 1 >= 0 && data -> map[(int)r.y - 1][(int)r.x] == -1)
			ray->tex = data -> door_open;
	}
}
