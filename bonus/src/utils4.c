/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:05:24 by vluo              #+#    #+#             */
/*   Updated: 2025/06/16 18:00:41 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	free_sprites(t_data	*data)
{
	int	i;
	int	j;

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
