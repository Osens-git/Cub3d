/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:53:31 by vluo              #+#    #+#             */
/*   Updated: 2025/06/06 15:42:32 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	is_pos_in_res(float x, float y)
{
	return (0 <= x / CELLSIZE && x / CELLSIZE < 8
		&& 0 <= y / CELLSIZE && y / CELLSIZE < 8);
}
