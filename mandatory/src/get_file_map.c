/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:00:44 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/06/22 14:54:08 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_correct_line(char *line, int count)
{
	if (ft_strncmp(line, "\n", 2) == 0)
		return (count);
	if (ft_strncmp(line, "NO ", 3) == 0 \
	|| ft_strncmp(line, "SO ", 3) == 0 \
	|| ft_strncmp(line, "EA ", 3) == 0 \
	|| ft_strncmp(line, "WE ", 3) == 0 \
	|| ft_strncmp(line, "F ", 2) == 0 \
	|| ft_strncmp(line, "C ", 2) == 0)
		return (++count);
	if (count < 6)
		return (-1);
	return (count);
}

static char	*stock_read_line(int fd, char *stock)
{
	char	*line;
	char	*tmp;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count = check_correct_line(line, count);
		if (count == -1)
			return (free(line), free(stock),
				exit_mess("Invalid argument in file"), NULL);
		tmp = stock;
		stock = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		if (!stock)
			return (close(fd), exit_mess("Memory allocation failed"), NULL);
	}
	return (stock);
}

char	**get_file_map(char *file)
{
	int		fd;
	char	*stock;
	char	**file_map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (exit_mess("The map couldn't be opened"), NULL);
	stock = ft_strdup("");
	if (!stock)
		return (close(fd), exit_mess("Memory allocation failed"), NULL);
	stock = stock_read_line(fd, stock);
	if (!stock)
		return (NULL);
	file_map = ft_split(stock, '\n');
	free(stock);
	if (!file_map || file_map[0] == NULL)
		return (free_tab(file_map), close(fd), exit_mess("Empty file"), NULL);
	return (close(fd), file_map);
}
