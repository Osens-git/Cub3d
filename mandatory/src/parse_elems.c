/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:50:20 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/06/23 10:36:38 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_digit(char *line)
{
	int	nb;
	int	i;

	nb = 1;
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i ++;
	if (!line[i] || (line[i] != '+' && line[i] != '-' && !ft_isdigit(line[i])))
		return (0);
	if (line[i] == '-' || line[i] == '+')
		if (line[i++] == '-')
			nb = -1;
	while (line[i] && line[i] == '0')
		i ++;
	nb *= ft_atoi(&line[i]);
	if (nb >= 0 && nb <= 255 && ft_strlen(&line[i]) <= 4)
		return (1);
	return (0);
}

static int	stock_color(char *line, t_color *color, int *col)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	tmp = ft_split(line, ',');
	while (tmp[i])
		i++;
	if (i != 3)
		return (free_tab(tmp), exit_mess("EXIT_NB_RGB"));
	i = -1;
	while (tmp[++i])
	{
		j = 0;
		if (tmp[i][j] == ' ')
			j++;
		if (!is_digit(tmp[i]))
			return (free_tab(tmp), exit_mess(EXIT_COLOR));
	}
	color->r = atoi(tmp[0]);
	color->g = atoi(tmp[1]);
	color->b = atoi(tmp[2]);
	if (!check_limits(color))
		return (free_tab(tmp), 0);
	return (free_tab(tmp), *col = trgb(0, color->r, color->g, color->b), 1);
}

static int	parse_color(char *line, t_data *data)
{
	int		j;
	t_color	col;

	j = 1;
	if (line[0] == 'F')
	{
		while (line[j] == ' ')
			j ++;
		return (stock_color(&line[j], &col, &data->floor_col));
	}
	while (line[j] == ' ')
		j ++;
	return (stock_color(&line[j], &col, &data->ceiling_col));
}

static int	parse_texture(t_data *data, t_img **dir, char *line)
{
	int		w;
	int		h;
	char	**sp;
	t_img	*tex;

	if (*dir != NULL)
		return (exit_mess ("Only one texture per direction"), 0);
	sp = ft_split(line, ' ');
	tex = mlx_xpm_file_to_image(data->mlx, sp[1], &w, &h);
	free_tab(sp);
	if (tex == NULL)
		return (exit_mess("Error with texture file"), 0);
	*dir = init_img(data, tex);
	if (!*dir)
		return (exit_mess("Malloc error"), 0);
	return (1);
}

int	parse_elems(t_data *data, int start, char **file)
{
	int	i;

	i = -1;
	while (++i < start)
	{
		if (file[i][0] == 'F' || file[i][0] == 'C')
			if (parse_color(file[i], data) == 0)
				return (0);
		if (ft_strncmp(file[i], "NO ", 3) == 0)
			if (!parse_texture(data, &data -> no, file[i]))
				return (0);
		if (ft_strncmp(file[i], "SO ", 3) == 0)
			if (!parse_texture(data, &data -> so, file[i]))
				return (0);
		if (ft_strncmp(file[i], "EA ", 3) == 0)
			if (!parse_texture(data, &data -> ea, file[i]))
				return (0);
		if (ft_strncmp(file[i], "WE ", 3) == 0)
			if (!parse_texture(data, &data -> we, file[i]))
				return (0);
	}
	return (1);
}
