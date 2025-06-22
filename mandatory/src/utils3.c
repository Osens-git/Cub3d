/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:46:41 by vluo              #+#    #+#             */
/*   Updated: 2025/06/22 15:15:26 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	free_tab_int(int **t)
{
	int	i;

	if (t == 0)
		return ;
	i = -1;
	while (t[++i])
		free(t[i]);
	free(t);
}

void	free_img(t_data *data, t_img *img)
{
	mlx_destroy_image(data->mlx, img->img);
	free(img);
}
