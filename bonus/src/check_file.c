/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:50:32 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/06/23 11:23:14 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	check_arg(int ac, char **av)
{
	char	*ret;
	int		len;

	if (ac != 2)
		return (exit_mess("the command must contain 2 arguments"));
	len = ft_strlen(av[1]);
	ret = NULL;
	while (len >= 0 && av[1][len] != '.')
		len--;
	if (av[1][len] == '.')
		ret = ft_strdup(&av[1][len + 1]);
	if (!ret || !(ft_strncmp(ret, "cub", 7) == 0))
	{
		free(ret);
		return (exit_mess("It must be a .cub file"));
	}
	free(ret);
	return (1);
}

int	check_nb_tex_col(char **file, int start)
{
	int	i;
	int	c_tex;
	int	c_col;

	c_tex = 0;
	c_col = 0;
	i = -1;
	while (++i < start)
	{
		if (ft_strncmp(file[i], "NO ", 3) == 0 \
			|| ft_strncmp(file[i], "SO ", 3) == 0 \
			|| ft_strncmp(file[i], "WE ", 3) == 0 \
			|| ft_strncmp(file[i], "EA ", 3) == 0)
			c_tex ++;
		if (ft_strncmp(file[i], "F ", 2) == 0
			|| ft_strncmp(file[i], "C ", 2) == 0)
			c_col ++;
	}
	if (c_tex != 4)
		return (exit_mess(EXIT_NB_TEX));
	if (c_col != 2)
		return (exit_mess(EXIT_NB_COL));
	return (1);
}

static int	is_rem_all_sp(char **map, int i, int j)
{
	int	dir;
	int	k;

	if (!(map[i][j] == '0' || map[i][j] == '2'))
		return (1);
	dir = 1;
	if (map[i + 1] == 0)
		dir = -1;
	k = j;
	if (map[i + dir])
	{
		while (map[i + dir][k]
			&& (map[i + dir][k] == ' ' || map[i + dir][k] == '1'))
			k ++;
		if (!map[i + dir][k])
			return (1);
	}
	return (0);
}

int	check_surrounded(char **map, int y, int st)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < y)
	{
		if (i == 0 || i == y - 1)
		{
			j = -1;
			while (map[st + i][++j])
			{
				if ((map[st + i][j] != '1' && map[st + i][j] != '0'
						&& map[st + i][j] != '2' && map[st + i][j] != ' ')
						|| is_rem_all_sp(map, st + i, j) == 0)
					return (exit_mess(EXIT_MAP));
			}
			continue ;
		}
		len = ft_strlen(map[st + i]);
		if ((map[st + i][0] != '1' && map[st + i][0] != ' ')
			|| (map[st + i][len - 1] != '1' && map[st + i][len - 1] != ' '))
			return (exit_mess(EXIT_MAP));
	}
	return (1);
}

int	check_map(char **file, int start)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	len = 0;
	while (file[start + ++i])
	{
		j = -1;
		while (file[start + i][++j])
		{
			if (file[start + i][j] != 'N' && file[start + i][j] != 'S' \
				&& file[start + i][j] != 'E' && file[start + i][j] != 'W' \
				&& file[start + i][j] != '1' && file[start + i][j] != '0' \
				&& file[start + i][j] != ' ' && file[start + i][j] != '2')
				return (exit_mess("Invalid char in map"));
			if (file[start + i][j] == 'N' || file[start + i][j] == 'S' \
				|| file[start + i][j] == 'E' || file[start + i][j] == 'W')
				len ++;
		}
	}
	if (len != 1)
		return (exit_mess("There must be one staring position"));
	return (1);
}
