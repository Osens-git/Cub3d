/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:52:18 by vluo              #+#    #+#             */
/*   Updated: 2025/06/05 12:52:50 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
