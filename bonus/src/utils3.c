/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:05:24 by vluo              #+#    #+#             */
/*   Updated: 2025/06/23 11:00:54 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	free_sprites(t_data	*data)
{
	int	i;
	int	j;

	if (!data -> sprites)
		return ;
	i = -1;
	while (data->sprites[++i])
	{
		j = -1;
		while (data->sprites[i]->textures[++j])
			free_img(data, data->sprites[i]->textures[j]);
		free(data->sprites[i]->textures);
		free(data->sprites[i]);
	}
	free(data -> sprites);
}

void	free_img(t_data *data, t_img *img)
{
	mlx_destroy_image(data->mlx, img->img);
	free(img);
}

t_img	*xpm_img(t_data *data, char *file)
{
	int	w;
	int	h;

	return (mlx_xpm_file_to_image(data->mlx, file, &w, &h));
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_limits(t_color *color)
{
	if (color->r < 0 || color->r > 255 \
		|| color->g < 0 || color->g > 255 \
		|| color->b < 0 || color->b > 255)
		return (exit_mess("Colors must be on a range 0-255"));
	return (1);
}
