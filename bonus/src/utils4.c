/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:04:14 by vluo              #+#    #+#             */
/*   Updated: 2025/06/22 19:28:34 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
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

void	free_minimap(t_data *data)
{
	if (!data->minimap)
		return ;
	if (data->minimap->m)
		free_img(data, data->minimap->m);
	free(data->minimap->st);
	free(data->minimap->end);
	free(data->minimap->size);
	free(data->minimap);
}

void	free_player(t_data *data)
{
	if (!data -> p)
		return ;
	free(data->p->pos);
	free(data->p->d);
	free(data->p->near_door);
	free(data->p);
}

int	exit_mess(char *message)
{
	ft_printf(RED"\nError\n"GREY"%s\n"RESET, message);
	return (0);
}
