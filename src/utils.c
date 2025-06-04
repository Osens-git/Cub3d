/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:24:51 by vluo              #+#    #+#             */
/*   Updated: 2025/06/04 18:45:56 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	*init_img(t_data *data, void *img_ptr)
{
	t_img	*img;

	img = calloc(1, sizeof(t_img));
	if (img_ptr == NULL)
		img -> img = mlx_new_image(data->mlx, RES_X, RES_Y);
	else
		img -> img = img_ptr;
	img -> addr = mlx_get_data_addr(img->img, &img->b_p_p,
			&img->line_length, &img->endian);
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

void	free_data(t_data *data)
{
	int	i;

	mlx_destroy_image(data -> mlx, data -> img -> img);
	free(data -> img);
	// mlx_destroy_image(data -> mlx, data -> no -> img);
	// free(data -> no);
	// mlx_destroy_image(data -> mlx, data -> no);
	// mlx_destroy_image(data -> mlx, data -> img -> img);
	// free(data -> img);
	// mlx_destroy_image(data -> mlx, data -> img -> img);
	// free(data -> img);
	// mlx_destroy_image(data -> mlx, data -> img -> img);
	// free(data -> img);
	mlx_destroy_window(data -> mlx, data -> win);
	mlx_destroy_display(data -> mlx);
	free(data -> mlx);
	free(data -> p -> pos);
	free(data -> p -> d);
	free(data -> p);
	i = -1;
	while (++i < 8)
		free(data->map[i]);
	free(data->map);
	free(data);
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

float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

t_array	*init_array(void)
{
	t_array	*tab;

	tab = ft_calloc(1, sizeof(t_array));
	if (tab == 0)
		return (NULL);
	tab -> tot_len = 2;
	tab -> arr_i = 0;
	tab -> arr = ft_calloc(3, sizeof(char *));
	if (tab -> arr == 0)
		return (free(tab), NULL);
	return (tab);
}

char	**append(char **sp, int *len_tot, int *sp_i, char *sub)
{
	int		i;
	char	**split_double;

	if (sub == 0)
		return (free_tab(sp), NULL);
	if (*sp_i < *len_tot)
	{
		*sp_i += 1;
		return (sp[*sp_i - 1] = sub, sp);
	}
	split_double = ft_calloc((*len_tot * 2) + 1, sizeof(char *));
	if (!split_double)
		return (free_tab(sp), NULL);
	i = -1;
	while (sp[++i])
		split_double[i] = sp[i];
	return (split_double[i] = sub, split_double[i + 1] = 0,
		*len_tot = *len_tot * 2, *sp_i = i + 1, free(sp), split_double);
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
