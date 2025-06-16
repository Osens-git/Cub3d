/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:53:31 by vluo              #+#    #+#             */
/*   Updated: 2025/06/16 19:06:15 by vluo             ###   ########.fr       */
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
