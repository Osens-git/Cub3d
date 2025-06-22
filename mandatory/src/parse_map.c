/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:02:36 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/06/22 19:35:07 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	size_map(t_data *data, char **f)
{
	int	i;
	int	len;
	int	count;
	int	max;
	int	st;

	i = 0;
	while (f[i] && (ft_strncmp(f[i], "NO ", 3) == 0 \
		|| ft_strncmp(f[i], "SO ", 3) == 0 || ft_strncmp(f[i], "WE ", 3) == 0 \
		|| ft_strncmp(f[i], "EA ", 3) == 0 || ft_strncmp(f[i], "C ", 2) == 0 \
		|| ft_strncmp(f[i], "F ", 2) == 0))
		i++;
	st = i--;
	count = 0;
	max = 0;
	while (f[++i])
	{
		len = ft_strlen(f[i]);
		if (len > max)
			max = len;
		count++;
	}
	if (count == 0)
		return (exit_mess("No map in file"), -1);
	return (data->m_size = init_pos(max, count), st);
}

void	egalize_map(t_data *data, int start, char **file)
{
	char	*new_line;
	int		len;
	int		i;
	int		max;

	i = 0;
	max = data->m_size->x;
	len = 0;
	while (i < data->m_size->y)
	{
		len = ft_strlen(file[start + i]);
		if (len < max)
		{
			new_line = (char *)malloc(sizeof(char) * (max + 1));
			if (!new_line)
				return ;
			ft_strcpy(new_line, file[start + i]);
			while (len < max)
				new_line[len++] = ' ';
			new_line[len] = '\0';
			free(file[start + i]);
			file[start + i] = new_line;
		}
		i++;
	}
}

static void	get_in_line(char *line, int *start, int *end)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] && line[i] == ' ')
		i ++;
	*start = i;
	while (line[i] && line[++i])
	{
		j = i;
		while (line[j] && line[j] == ' ')
			j ++;
		if (!line[j])
			*end = i;
		i = j;
	}
	if (i != 0 && *end == 0)
		*end = i;
}

static int	*replace_line(char *line, t_data *data, int y)
{
	int	i;
	int	st;
	int	end;
	int	*res;

	st = 0;
	end = 0;
	get_in_line(line, &st, &end);
	res = ft_calloc(data->m_size->x, sizeof(int));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < data->m_size->x)
	{
		if (line[i] == 'N' || line[i] == 'W'
			|| line[i] == 'E' || line[i] == 'S')
			init_player(data, init_pos(i * CELLSIZE + (CELLSIZE / 2),
					y * CELLSIZE + (CELLSIZE / 2)), line[i]);
		res[i] = 0;
		if (ft_isdigit(line[i]))
			res[i] = line[i] - '0';
		if (i <= st || i >= end)
			res[i] = 1;
	}
	return (res);
}

int	**parse_map(t_data *data, int start, char **file)
{
	int	i;
	int	j;
	int	**map;

	map = ft_calloc(data->m_size->y + 1, sizeof(int *));
	i = -1;
	while (++i < data->m_size->y)
	{
		if (i == 0 || i == data->m_size->y - 1)
		{
			map[i] = ft_calloc(data->m_size->x, sizeof(int));
			if (!map[i])
				return (free_tab_int(map), NULL);
			j = -1;
			while (++j < data->m_size->x)
				map[i][j] = 1;
		}
		else
		{
			map[i] = replace_line(file[start + i], data, i);
			if (!map[i])
				return (free_tab_int(map), NULL);
		}
	}
	return (map);
}
