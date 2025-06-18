/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:36:03 by vluo              #+#    #+#             */
/*   Updated: 2025/06/18 12:55:53 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	*init_tab(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9)
{
	int	*t;

	t = ft_calloc(9, sizeof(int));
	t[0] = n1;
	t[1] = n2;
	t[2] = n3;
	t[3] = n4;
	t[4] = n5;
	t[5] = n6;
	t[6] = n7;
	t[7] = n8;
	t[8] = n9;
	return (t);
}

int	**init_map(void)
{
	int	**map;

	map = ft_calloc(8, sizeof(int *));
	map[0] = init_tab(1, 1, 1, 1, 1, 1, 1, 1, 1);
	map[1] = init_tab(1, 0, 1, 0, 0, 0, 0, 1, 1);
	map[2] = init_tab(1, 0, 1, 0, 0, 0, 0, 1, 1);
	map[3] = init_tab(1, 0, 1, 0, 0, 0, 0, 0, 1);
	map[4] = init_tab(1, 0, 1, 0, 0, 0, 0, 0, 1);
	map[5] = init_tab(1, 0, 0, 0, 0, 0, 0, 0, 1);
	map[6] = init_tab(1, 0, 0, 0, 0, 0, 0, 0, 1);
	map[7] = init_tab(1, 1, 1, 1, 1, 1, 1, 1, 1);
	return (map);
}
